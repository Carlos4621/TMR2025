#include "YOLOv8Displayer.h"

namespace My {

YOLOv8Displayer::YOLOv8Displayer(const YOLOv8ModelParams &modelParams, QWidget *parent)
    : QTextEdit{ parent }
    , model_m{modelParams} {
    setReadOnly(true);
    setFocusPolicy(Qt::NoFocus);
}

void YOLOv8Displayer::detectAndDisplay(const cv::Mat &image) {
    const auto data{ std::move(model_m.getPredictions(image)) };

    if (data.empty()) {
        clear();
    }

    for(const auto& i: data) {
        insertPlainText(i.className.c_str());
        insertPlainText("\n");
    }
}

} // namespace My
