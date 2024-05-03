#pragma once
#ifndef INFERENCES_DATA_HEADER
#define INFERENCES_DATA_HEADER

#include <cstdint>
#include <string>
#include <opencv4/opencv2/opencv.hpp>

namespace My {

    /// @brief Struct que contiene los datos de las predicciones
    struct PredictionsData {
        uint16_t classID;
        std::string className;
        double confidence;
        cv::Rect bouncingBox;
    };
}

#endif //!INFERENCES_DATA_HEADER
