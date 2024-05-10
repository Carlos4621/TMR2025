#pragma once
#ifndef QRDISPLAYER_H
#define QRDISPLAYER_H

#include <QWidget>
#include <opencv4/opencv2/opencv.hpp>
#include <QTextEdit>
#include <QLayout>

namespace My {

/// @brief Clase capaz de decodificar un QR detectado en una cv::Mat y mostrarlo en un QTextEdit
class QRDisplayer : public QTextEdit {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param parent Padre del widget
    explicit QRDisplayer(QWidget *parent = nullptr);

    /// @brief Detecta, decodifica y lo muestra en un TextEdit
    /// @param image Imagen a ser procesada
    void decodifyAndDisplay(const cv::Mat& image);

private:

    cv::QRCodeDetector QRDetector_m;
};

} // namespace My

#endif // !QRDISPLAYER_H
