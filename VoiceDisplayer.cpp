#include "VoiceDisplayer.h"

namespace My {

VoiceDisplayer::VoiceDisplayer(std::string_view modelPath, QWidget *parent)
    : QTextEdit{parent}
    , stt_m{ new My::Susurrador{ modelPath } }
{
    stt_m->moveToThread(&workerThread_m);

    connect(&workerThread_m, &QThread::finished, stt_m, &QObject::deleteLater);
    connect(this, &VoiceDisplayer::transcribeAudio, stt_m, &Susurrador::manageAudio);
    connect(stt_m, &Susurrador::resultReady, this, &VoiceDisplayer::setText);
    connect(stt_m, &Susurrador::resultReady, this, &VoiceDisplayer::trasnscriptionDisplayed);

    workerThread_m.start();

    setReadOnly(true);
    setFocusPolicy(Qt::NoFocus);
}

} // namespace My
