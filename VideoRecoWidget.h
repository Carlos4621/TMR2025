#pragma once
#ifndef RECOWIDGET_H
#define RECOWIDGET_H

#include <QWidget>
#include "YOLOv8Model.h"
#include <QCheckBox>
#include <QTimer>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QtConcurrent>

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

    void onNextFrame();
    void onModelPredictionFinished();
    void onQRDetectionFinished();

private:

    QLabel* videoLabel_m{ nullptr };

    QTextEdit* QRTextEdit_m{ nullptr };
    cv::QRCodeDetector QRCodeDetector_m;

    QTextEdit* modelTextEdit_m{ nullptr };
    YOLOv8Model* model_m{ nullptr };

    QCheckBox* QRCheck_m{ nullptr };
    QCheckBox* hazmatCheck_m{ nullptr };

    QTimer* timer_m{ nullptr };

    cv::VideoCapture camera_m;
    cv::Mat currentFrame_m;

    bool isModelPredictionsRunning_m{ false };
    QFutureWatcher<std::vector<PredictionsData>>* predictionsFuture_m{ nullptr };

    bool isQRDetectionRunning_m{ false };
    QFutureWatcher<std::string>* QRFuture_m{ nullptr };

    void setupLayout();

    QPixmap matToPixmap(const cv::Mat&);

    void startModelPredictions();
    void startQRDetection();
};

} // namespace My

#endif // !RECOWIDGET_H
