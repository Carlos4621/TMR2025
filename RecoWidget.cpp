#include "RecoWidget.h"

namespace My {

RecoWidget::RecoWidget(QWidget *parent) : QWidget{ parent }, videoLabel_m{ new VideoLabel{this} }, QRText_m{ new QRLabel{this} }, hazmatText_m{ new HazmatLabel{this} },
    QRCheck_m{ new QCheckBox{this} }, hazmatCheck_m{ new QCheckBox{this} } {

    QRCheck_m->setText("Enable QR");
    hazmatCheck_m->setText("Enable Hazmat");
    setupLayout();
}

void RecoWidget::updateVideo() {
    cv::Mat frame;

    camera_m >> frame;

    videoLabel_m->setImage(frame);

    if(QRCheck_m->isChecked()) {
        QRText_m->decodifyAndShow(frame);
    }

    if(hazmatCheck_m->isChecked()) {
        hazmatText_m->detectAndDisplay(frame);
    }
}

void RecoWidget::setCameraID(const uint8_t &ID) {
    camera_m.open(ID);

    if(!camera_m.isOpened()) {
        throw std::runtime_error{ "Unable to open the camera" };
    }
}

void RecoWidget::setModelParams(const YOLOv8ModelParams &modelParams) {
    hazmatText_m->initializeModel(modelParams);
}

void RecoWidget::setupLayout() {

    QGridLayout* layout{ new QGridLayout{this} };

    layout->setContentsMargins(0, 0, 0, 0);

    videoLabel_m->setMinimumSize(QSize(640, 480));

    layout->addWidget(videoLabel_m, 0, 0, 4, 1);

    QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hazmatText_m->sizePolicy().hasHeightForWidth());

    hazmatText_m->setSizePolicy(sizePolicy);

    layout->addWidget(hazmatText_m, 3, 1, 1, 1);

    sizePolicy.setHeightForWidth(QRText_m->sizePolicy().hasHeightForWidth());
    QRText_m->setSizePolicy(sizePolicy);

    layout->addWidget(QRText_m, 0, 1, 1, 1);

    layout->addWidget(QRCheck_m, 1, 1, 1, 1);

    layout->addWidget(hazmatCheck_m, 2, 1, 1, 1);
}

} // namespace My
