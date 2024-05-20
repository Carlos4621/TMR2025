#include "VideoRecoWidget.h"

namespace My {

RecoWidget::RecoWidget(const uint8_t& cameraID, const YOLOv8ModelParams &modelParams, const uint16_t& maxFPS, QWidget *parent)
    : QWidget{ parent }
    , videoLabel_m{ new QLabel{this} }
    , QRTextEdit_m{ new QTextEdit{this} }
    , modelTextEdit_m{ new QTextEdit{this} }
    , model_m{ new YOLOv8Model{modelParams, this} }
    , QRCheck_m{ new QCheckBox{ tr("Enable QR"), this} }
    , hazmatCheck_m{ new QCheckBox{ tr("Enable Hazmat"), this} }
    , timer_m{ new QTimer{this} }
    , camera_m{ cameraID }
    , predictionsFuture_m{ new QFutureWatcher<std::vector<PredictionsData>>{this} }
    , QRFuture_m{ new QFutureWatcher<std::string>{this} }
{
    timer_m->setInterval(1000 / maxFPS);

    connect(timer_m, &QTimer::timeout, this, &RecoWidget::onNextFrame);
    connect(predictionsFuture_m, &QFutureWatcher<std::vector<PredictionsData>>::finished, this, &RecoWidget::onModelPredictionFinished);
    connect(QRFuture_m, &QFutureWatcher<std::string>::finished, this, &RecoWidget::onQRDetectionFinished);

    setupLayout();

    timer_m->start();
}

void RecoWidget::onNextFrame() {
    camera_m >> currentFrame_m;

    if(QRCheck_m->isChecked() && !isQRDetectionRunning_m) {
        startQRDetection();
    }

    if(hazmatCheck_m->isChecked() && !isModelPredictionsRunning_m) {
        startModelPredictions();
    }

    videoLabel_m->setPixmap(matToPixmap(currentFrame_m));
}

void RecoWidget::onModelPredictionFinished() {
    modelTextEdit_m->clear();

    for(const auto& i : predictionsFuture_m->result()) {
        modelTextEdit_m->insertPlainText(i.className.c_str());
        modelTextEdit_m->insertPlainText("\n");
    }

    isModelPredictionsRunning_m = false;
}

void RecoWidget::onQRDetectionFinished() {
    QRTextEdit_m->setText(QRFuture_m->result().c_str());

    isQRDetectionRunning_m = false;
}

void RecoWidget::setupLayout() {

    QGridLayout* layout{ new QGridLayout{this} };

    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(videoLabel_m, 0, 0, 4, 1);

    QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(modelTextEdit_m->sizePolicy().hasHeightForWidth());

    modelTextEdit_m->setSizePolicy(sizePolicy);

    layout->addWidget(modelTextEdit_m, 3, 1, 1, 1);

    sizePolicy.setHeightForWidth(QRTextEdit_m->sizePolicy().hasHeightForWidth());
    QRTextEdit_m->setSizePolicy(sizePolicy);

    layout->addWidget(QRTextEdit_m, 0, 1, 1, 1);
    layout->addWidget(QRCheck_m, 1, 1, 1, 1);
    layout->addWidget(hazmatCheck_m, 2, 1, 1, 1);

    modelTextEdit_m->setReadOnly(true);
    modelTextEdit_m->setFocusPolicy(Qt::NoFocus);

    QRTextEdit_m->setReadOnly(true);
    QRTextEdit_m->setFocusPolicy(Qt::NoFocus);
}

QPixmap RecoWidget::matToPixmap(const cv::Mat& image) {
    const QImage qtImage(reinterpret_cast<uint8_t*>(image.data), image.cols, image.rows, image.step, QImage::Format_BGR888);

    return QPixmap::fromImage(qtImage);
}

void RecoWidget::startModelPredictions() {
    predictionsFuture_m->setFuture(QtConcurrent::run(&YOLOv8Model::getPredictions, model_m, currentFrame_m, 0.25, 0.45, 0.5));

    isModelPredictionsRunning_m = true;
}

void RecoWidget::startQRDetection() {
    QRFuture_m->setFuture(QtConcurrent::run(&cv::QRCodeDetector::detectAndDecode, QRCodeDetector_m, currentFrame_m, cv::noArray(), cv::noArray()));

    isQRDetectionRunning_m = true;
}

} // namespace My
