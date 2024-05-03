#include "QRLabel.h"

namespace My {

QRLabel::QRLabel(QWidget *parent) : QWidget{ parent }, textEdit_m{ new QTextEdit{this} } {
    QHBoxLayout* layout{ new QHBoxLayout{this} };

    layout->addWidget(textEdit_m);

    textEdit_m->setReadOnly(true);
}

void QRLabel::decodifyAndShow(const cv::Mat &image) {
    textEdit_m->setText(QRDetector_m.detectAndDecode(image).c_str());
}

} // namespace My
