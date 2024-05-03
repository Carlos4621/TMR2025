#pragma once
#ifndef VIDEOLABEL_H
#define VIDEOLABEL_H

#include <QWidget>
#include <QLabel>
#include <opencv4/opencv2/opencv.hpp>
#include <QLayout>

namespace My {

/// @brief Label que permite la colocación de imagenes cv::Mat
class VideoLabel : public QWidget {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param parent Padre del widget
    explicit VideoLabel(QWidget* parent = nullptr);

    /// @brief Coloca una imagen en el label
    /// @param image Imagen a colocar
    void setImage(const cv::Mat& image);

private:
    QLabel* label_m;

};

} // namespace My

#endif // VIDEOLABEL_H
