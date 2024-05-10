#pragma once
#ifndef RECOWIDGET_H
#define RECOWIDGET_H

#include <QWidget>
#include "QRDisplayer.h"
#include "YOLOv8Displayer.h"
#include <QCheckBox>
#include "ImageLabel.h"
#include <QTimer>

namespace My {

/// @brief Clase que representa una colección de Widgets para el reconocimiento de códigos QR y Hazmat Labels
class RecoWidget : public QWidget {
    Q_OBJECT
public:

    /// @brief Contructor base
    /// @param cameraID ID de la cámara a abrir
    /// @param modelParams Parámetros para inciar el modelo a usar
    /// @param maxFPS FPS máximos para la cámara
    /// @param parent Padre del widget
    RecoWidget(const uint8_t& cameraID, const YOLOv8ModelParams& modelParams, const uint16_t& maxFPS, QWidget *parent = nullptr);

private slots:

    void updateVideo();

private:
    VideoLabel* videoLabel_m;

    QRDisplayer* QRDisplayer_m;
    YOLOv8Displayer* hazmatDisplayer_m;

    QCheckBox* QRCheck_m;
    QCheckBox* hazmatCheck_m;

    QTimer* timer_m;

    cv::VideoCapture camera_m;

    void setupLayout();
};

} // namespace My

#endif // RECOWIDGET_H
