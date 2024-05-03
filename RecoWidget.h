#pragma once
#ifndef RECOWIDGET_H
#define RECOWIDGET_H

#include <QWidget>
#include "QRLabel.h"
#include "HazmatLabel.h"
#include <QCheckBox>
#include "VideoLabel.h"

namespace My {

/// @brief Clase que representa una colección de Widgets para el reconocimiento de códigos QR y Hazmat Labels
class RecoWidget : public QWidget {
    Q_OBJECT
public:

    /// @brief Contructor base
    /// @param parent Padre del widget
    explicit RecoWidget(QWidget *parent = nullptr);

    /// @brief Encargado de realizar la actualiación del video y el reconocimiento en este
    void updateVideo();

    /// @brief Abre la cámara con el ID propocionado
    /// @param ID ID a colocar
    void setCameraID(const uint8_t& ID);

    /// @brief Inicializa el modelo de reconocimiento a usar
    /// @param modelParams Parámetros del modelo a usar
    void setModelParams(const YOLOv8ModelParams& modelParams);

private:
    VideoLabel* videoLabel_m;

    QRLabel* QRText_m;
    HazmatLabel* hazmatText_m;

    QCheckBox* QRCheck_m;
    QCheckBox* hazmatCheck_m;

    cv::VideoCapture camera_m;

    void setupLayout();
};

} // namespace My

#endif // RECOWIDGET_H
