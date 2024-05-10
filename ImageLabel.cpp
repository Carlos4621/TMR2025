#include "ImageLabel.h"

namespace My {

VideoLabel::VideoLabel(QWidget *parent)
    : QLabel{ parent } {
    setScaledContents(true);
}

void VideoLabel::setImage(const cv::Mat & image) {
    const QImage qtImage(reinterpret_cast<uint8_t*>(image.data), image.cols, image.rows, image.step, QImage::Format_BGR888);

    const QPixmap pixmap{ QPixmap::fromImage(qtImage) };

    setPixmap(pixmap);
}

} // namespace My
