#include "VideoRecoWidget.h"

namespace My {

RecoWidget::RecoWidget(const uint8_t& cameraID, const YOLOv8ModelParams &modelParams, const uint16_t& maxFPS, QWidget *parent)
    : QWidget{ parent }
    , videoLabel_m{ new QLabel{this} }
    , QRTextEdit_m{ new QTextEdit{this} }
    , modelTextEdit_m{ new QTextEdit{this} }
    , model_m{ new YOLOv8Model{modelParams} }
    , QRCheck_m{ new QCheckBox{ tr("Enable QR"), this} }
    , hazmatCheck_m{ new QCheckBox{ tr("Enable Hazmat"), this} }
    , timer_m{ new QTimer{this} }
    , camera_m{ cameraID }
{
    timer_m->setInterval(1000 / maxFPS);

    connect(timer_m, &QTimer::timeout, this, &RecoWidget::onNextFrame);
    connect(&predictions_m, &QFutureWatcher<std::vector<PredictionsData>>::finished, this, &RecoWidget::onAsyncFinish);

    setupLayout();

    timer_m->start();
}

void RecoWidget::onNextFrame() {
    cv::Mat frame;

    camera_m >> frame;

    if(QRCheck_m->isChecked()) {
        QRTextEdit_m->setText(QRCodeDetector_m.detectAndDecode(frame).c_str());
    }

    if(hazmatCheck_m->isChecked() && !isPredictionsRunning) {
        processPredictions(frame);
    }

    videoLabel_m->setPixmap(matToPixmap(frame));
}

void RecoWidget::onAsyncFinish() {
    modelTextEdit_m->clear();

    for(const auto& i : predictions_m.result()) {
        modelTextEdit_m->insertPlainText(i.className.c_str());
        modelTextEdit_m->insertPlainText("\n");
    }

    isPredictionsRunning = false;
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

void RecoWidget::processPredictions(const cv::Mat& frame) {
    predictions_m.setFuture(QtConcurrent::run(&YOLOv8Model::getPredictions, model_m, frame, 0.25, 0.45, 0.5));

    isPredictionsRunning = true;
}

} // namespace My
