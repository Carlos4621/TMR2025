#include "HazmatLabel.h"

namespace My {

HazmatLabel::HazmatLabel(QWidget *parent) : QWidget{ parent }, textEdit_m{ new QTextEdit{this} } {
    QHBoxLayout* layout{ new QHBoxLayout{ this } };

    layout->addWidget(textEdit_m);

    textEdit_m->setReadOnly(true);
}

void HazmatLabel::detectAndDisplay(const cv::Mat &image) {
    const auto data{ model_m.getPredictions(image) };

    if (data.empty()) {
        textEdit_m->setText("");
    }

    for(const auto& i: data) {
        textEdit_m->insertPlainText(i.className.c_str());
        textEdit_m->insertPlainText("\n");
    }
}

void HazmatLabel::initializeModel(const YOLOv8ModelParams &modelParams) {
    model_m.setParams(modelParams);
}

} // namespace My
