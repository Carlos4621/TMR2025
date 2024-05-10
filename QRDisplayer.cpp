#include "QRDisplayer.h"

namespace My {

QRDisplayer::QRDisplayer(QWidget *parent)
    : QTextEdit{ parent } {
    setReadOnly(true);
    setFocusPolicy(Qt::NoFocus);
}

void QRDisplayer::decodifyAndDisplay(const cv::Mat &image) {
    setText(QRDetector_m.detectAndDecode(image).c_str());
}

} // namespace My
