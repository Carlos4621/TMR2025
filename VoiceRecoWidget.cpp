#include "VoiceRecoWidget.h"

namespace My {

VoiceRecoWidget::VoiceRecoWidget(const QAudioDevice &device, const QAudioFormat &format, std::string_view voiceModelPath, QWidget *parent)
    : QWidget{parent}
    , recordButton_m{ new QPushButton{tr("Record"), this} }
    , stopButton_m{ new QPushButton{tr("Stop") ,this} }
    , voiceLabel_m{ new My::VoiceDisplayer{voiceModelPath, this} }
    , voiceRecorder_m{ new My::VoiceRecorder{device, format, this} }
{
    connect(recordButton_m, &QPushButton::pressed, this, &VoiceRecoWidget::onRecordPressed);
    connect(stopButton_m, &QPushButton::pressed, this, &VoiceRecoWidget::onStopPressed);
    connect(voiceLabel_m, &VoiceDisplayer::trasnscriptionDisplayed, this, &VoiceRecoWidget::onTransciptionDisplayed);

    stopButton_m->setEnabled(false);

    setupLayout();
}

void VoiceRecoWidget::onRecordPressed() {
    recordButton_m->setEnabled(false);
    stopButton_m->setEnabled(true);

    voiceLabel_m->clear();

    voiceRecorder_m->start();
}

void VoiceRecoWidget::onStopPressed() {
    stopButton_m->setEnabled(false);

    voiceRecorder_m->stop();

    emit voiceLabel_m->transcribeAudio(voiceRecorder_m->getBuffer().buffer());

    // Implementar algún tipo de marcador de cargado
}

void VoiceRecoWidget::onTransciptionDisplayed() {
    recordButton_m->setEnabled(true);
    // Implementar algún tipo de marcador de cargado
}

void VoiceRecoWidget::setupLayout() {

    QGridLayout* gridLayout{ new QGridLayout{this} };

    gridLayout->setHorizontalSpacing(10);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    gridLayout->addWidget(recordButton_m, 2, 0, 1, 1);

    QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(voiceLabel_m->sizePolicy().hasHeightForWidth());
    voiceLabel_m->setSizePolicy(sizePolicy);

    gridLayout->addWidget(voiceLabel_m, 0, 0, 1, 3);

    gridLayout->addWidget(stopButton_m, 2, 2, 1, 1);

    gridLayout->setColumnStretch(0, 5);
    gridLayout->setColumnStretch(2, 5);
}

} // namespace My
