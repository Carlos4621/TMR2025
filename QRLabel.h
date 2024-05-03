#pragma once
#ifndef QRLABEL_H
#define QRLABEL_H

#include <QWidget>
#include <opencv4/opencv2/opencv.hpp>
#include <QTextEdit>
#include <QLayout>

namespace My {

/// @brief Clase capaz de decodificar un QR detectado en una cv::Mat y mostrarlo en un TextEdit
class QRLabel : public QWidget {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param parent Padre del widget
    explicit QRLabel(QWidget *parent = nullptr);

    /// @brief Detecta, decodifica y lo muestra en un TextEdit
    /// @param image Imagen a ser procesada
    void decodifyAndShow(const cv::Mat& image);

private:
    QTextEdit* textEdit_m;

    cv::QRCodeDetector QRDetector_m;
};

} // namespace My

#endif // QRLABEL_H
