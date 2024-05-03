#include "YOLOv8Model.h"

My::YOLOv8Model::YOLOv8Model(std::string_view modelPath, const cv::Size& modelInputSize, std::string_view classesTxtPath, const bool& cudaEnabled) :
    YOLOv8Model{ YOLOv8ModelParams{modelPath.data(), modelInputSize, classesTxtPath.data(), cudaEnabled} } {
}

My::YOLOv8Model::YOLOv8Model(const YOLOv8ModelParams &params) {
    this->setParams(params);
}

std::vector<My::PredictionsData> My::YOLOv8Model::getPredictions(const cv::Mat &inputImage, const double& modelConfidenceThreshold, const double& modelScoreThreshold,
    const double& modelNMSThreshold) {

    cv::Mat blob;
    cv::dnn::blobFromImage(inputImage, blob, 1.0/255.0, modelInputSize_m, cv::Scalar{}, true);
    network_m.setInput(blob);

    std::vector<cv::Mat> networkOutputs;
    network_m.forward(networkOutputs);
    
    const auto rows{ networkOutputs[0].size[2] };
    const auto dimensions{ networkOutputs[0].size[1] };

    networkOutputs[0] = networkOutputs[0].reshape(1, dimensions);
    cv::transpose(networkOutputs[0], networkOutputs[0]);
    
    auto data{ reinterpret_cast<float*>(networkOutputs[0].data) };

    const auto Xfactor{ inputImage.cols / modelInputSize_m.width };
    const auto Yfactor{ inputImage.rows / modelInputSize_m.height };

    std::vector<uint8_t> classIDs;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (int i{ 0 }; i < rows; ++i) {

        auto const classes_scores{ data + 4 };

        cv::Mat scores(1, classNames_m.size(), CV_32FC1, classes_scores);
        cv::Point classID;
        double maxClassScore;

        cv::minMaxLoc(scores, 0, &maxClassScore, 0, &classID);

        if (maxClassScore > modelScoreThreshold) {
            
            confidences.push_back(maxClassScore);
            classIDs.push_back(classID.x);

            const auto& x{ data[0] };
            const auto& y{ data[1] };
            const auto& w{ data[2] };
            const auto& h{ data[3] };

            const auto left{ static_cast<int>((x - (0.5 * w)) * Xfactor) };
            const auto top{ static_cast<int>((y - (0.5 * h)) * Yfactor) };

            const auto width{ static_cast<int>(w * Xfactor) };
            const auto height{ static_cast<int>(h * Yfactor) };

            boxes.emplace_back(left, top, width, height);
        }

        data += dimensions;
    }

    std::vector<int> NMSResult;
    cv::dnn::NMSBoxes(boxes, confidences, modelScoreThreshold, modelNMSThreshold, NMSResult);

    std::vector<PredictionsData> inferences;

    for (const auto &i : NMSResult) {
        inferences.emplace_back(classIDs[i], classNames_m[classIDs[i]], confidences[i], boxes[i]);
    }
    
    return inferences;
}

void My::YOLOv8Model::setParams(const YOLOv8ModelParams &params) noexcept {
    modelInputSize_m = params.modelInputSize;

    loadOnnxNetwork(params.modelPath, params.runWithCUDA);
    loadClasses(params.classNamesPath);
}

void My::YOLOv8Model::loadClasses(std::string_view path) {

    if (std::ifstream inputFile(path.data()); inputFile.is_open()) {

        std::string classLine;

        while (std::getline(inputFile, classLine)) {
            classNames_m.push_back(classLine);
        }

    } 
    else {
        throw std::runtime_error{ "Unable to load class names file" };
    }
}

void My::YOLOv8Model::loadOnnxNetwork(std::string_view path, const bool& cudaEnabled) {
    network_m = cv::dnn::readNetFromONNX(path.data());

    if (cudaEnabled) {
        network_m.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        network_m.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    }
    else {
        network_m.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        network_m.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
}
