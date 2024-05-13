#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <opencv4/opencv2/opencv.hpp>
#include "VoiceRecorder.h"
#include <QtMultimedia>
#include "VideoRecoWidget.h"
#include "VoiceRecoWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    My::VoiceRecoWidget* reco;

    My::RecoWidget* vid;

    QTimer* timer;
};

#endif // MAINWINDOW_H
