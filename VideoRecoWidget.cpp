#include "VideoRecoWidget.h"

namespace My {

RecoWidget::RecoWidget(const uint8_t& cameraID, const YOLOv8ModelParams &modelParams, const uint16_t& maxFPS, QWidget *parent)
    : QWidget{ parent }
    , videoLabel_m{ new VideoLabel{this} }
    , QRDisplayer_m{ new QRDisplayer{this} }
    , hazmatDisplayer_m{ new YOLOv8Displayer{modelParams, this} }
    , QRCheck_m{ new QCheckBox{tr("Enable QR") ,this} }
    , hazmatCheck_m{ new QCheckBox{tr("Enable hazmat") ,this} }
    , camera_m(cameraID)
    , timer_m{ new QTimer{this} }
{
    timer_m->setInterval(1000 / maxFPS);

    connect(timer_m, &QTimer::timeout, this, &RecoWidget::updateVideo);

    setupLayout();

    timer_m->start();
}

void RecoWidget::updateVideo() {
    cv::Mat frame;

    camera_m >> frame;

    videoLabel_m->setImage(frame);

    if(QRCheck_m->isChecked()) {
        QRDisplayer_m->decodifyAndDisplay(frame);
    }

    if(hazmatCheck_m->isChecked()) {
        hazmatDisplayer_m->detectAndDisplay(frame);
    }
}

void RecoWidget::setupLayout() {

    QGridLayout* layout{ new QGridLayout{this} };

    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(videoLabel_m, 0, 0, 4, 1);

    QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hazmatDisplayer_m->sizePolicy().hasHeightForWidth());

    hazmatDisplayer_m->setSizePolicy(sizePolicy);

    layout->addWidget(hazmatDisplayer_m, 3, 1, 1, 1);

    sizePolicy.setHeightForWidth(QRDisplayer_m->sizePolicy().hasHeightForWidth());
    QRDisplayer_m->setSizePolicy(sizePolicy);

    layout->addWidget(QRDisplayer_m, 0, 1, 1, 1);

    layout->addWidget(QRCheck_m, 1, 1, 1, 1);

    layout->addWidget(hazmatCheck_m, 2, 1, 1, 1);
}

} // namespace My
