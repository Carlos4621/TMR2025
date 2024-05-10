#pragma once
#ifndef YOLOV8DISPLAYER_H
#define YOLOV8DISPLAYER_H

#include <QWidget>
#include <QTextEdit>
#include <opencv4/opencv2/opencv.hpp>
#include "YOLOv8Model.h"
#include <QBoxLayout>

namespace My {

/// @brief Clase que proporciona reconocimiento de imagenes para su despliegue en forma de texto
class YOLOv8Displayer : public QTextEdit {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param modelParams Parámetros para el modelo de detección a usar
    /// @param parent Puntero al widget padre
    YOLOv8Displayer(const YOLOv8ModelParams& modelParams, QWidget *parent = nullptr);

    /// @brief Recibe una imagen, detecta y muestra el objeto detectado
    /// @param image Imagen a utilizar
    void detectAndDisplay(const cv::Mat& image);

private:

    YOLOv8Model model_m;
};

} // namespace My

#endif // !YOLOV8DISPLAYER_H
