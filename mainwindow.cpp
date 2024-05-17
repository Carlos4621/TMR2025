#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer{new QTimer{this}}
{   //"/home/carlos4621/whisper.cpp/models/ggml-base.en.bin"

    ui->setupUi(this);

    const std::string modelPath{ "/home/carlos4621/whisper.cpp/models/ggml-base.en.bin" };

    const QAudioDevice audioDevice{ QMediaDevices::defaultAudioInput() };
    QAudioFormat format;
    format.setSampleRate(WHISPER_SAMPLE_RATE);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Float);

    reco = new My::VoiceRecoWidget{audioDevice, format, modelPath, this};

    reco->setGeometry(0, 0, 500, 500);

    const My::YOLOv8ModelParams modelParams{ "/home/carlos4621/TMR2025/hazmatModel.onnx", cv::Size{640, 640}, "/home/carlos4621/TMR2025/hazmatClasses.txt", false };

    vid = new My::RecoWidget{0, modelParams, 60, this};

    vid->setGeometry(200, 200, 700, 600);
}

MainWindow::~MainWindow() {
    delete ui;
}

