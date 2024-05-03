#pragma once
#ifndef HAZMATLABEL_H
#define HAZMATLABEL_H

#include <QWidget>
#include <QTextEdit>
#include <opencv4/opencv2/opencv.hpp>
#include "YOLOv8Model.h"
#include <QBoxLayout>

namespace My {

/// @brief Clase que proporciona identificación de etiquetas Hazmat
class HazmatLabel : public QWidget {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param parent Puntero al widget padre
    explicit HazmatLabel(QWidget *parent = nullptr);

    /// @brief Recibe una imagen, detecta y muestra la hazmat detectada
    /// @param image Imagen a utilizar
    void detectAndDisplay(const cv::Mat& image);

    /// @brief Inicializa el modelo para inferenciar las imagenes, de caso contrario se lanzará una excepción al intentar inferenciar
    /// @param modelParams Parámetros para inicializar el modelo
    void initializeModel(const YOLOv8ModelParams& modelParams);

private:
    QTextEdit* textEdit_m;

    YOLOv8Model model_m;
};

} // namespace My

#endif // HAZMATLABEL_H
