#include "VideoLabel.h"

namespace My {

VideoLabel::VideoLabel(QWidget *parent) : QWidget{parent}, label_m{new QLabel{this}} {
    QHBoxLayout* layout{ new QHBoxLayout{this} };

    layout->addWidget(label_m);

    label_m->setScaledContents(true);
}

void VideoLabel::setImage(const cv::Mat & image) {
    const QImage qtImage(reinterpret_cast<uchar*>(image.data), image.cols, image.rows, image.step, QImage::Format_BGR888);

    const QPixmap pixmap{ QPixmap::fromImage(qtImage) };

    label_m->setPixmap(pixmap);
}

} // namespace My
