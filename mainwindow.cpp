#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer{new QTimer}
{
    connect(timer, &QTimer::timeout, this, &MainWindow::updateVid);
    ui->setupUi(this);
    timer->setInterval(33);
    timer->start();

    const My::YOLOv8ModelParams modelParams{ "/home/carlos4621/TMR/hazmatModel.onnx", cv::Size{ 640, 640 }, "/home/carlos4621/TMR/hazmatClasses.txt", true };

    ui->videoFrente->setModelParams(modelParams);
    ui->videoFrente->setCameraID(0);

    ui->videoArriba->setModelParams(modelParams);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateVid() {
    ui->videoFrente->updateVideo();
}

