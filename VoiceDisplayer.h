#ifndef VOICEDISPLAYER_H
#define VOICEDISPLAYER_H

#include <QWidget>
#include <QTextEdit>
#include <QBuffer>
#include "Susurrador.h"
#include <QThread>

namespace My {

/// @brief Clase capaz de transcibir audio y mostrarlo en un QTextEdit
class VoiceDisplayer : public QTextEdit {
    Q_OBJECT
public:

    /// @brief Constructor base
    /// @param modelPath Path del modelo a usar
    /// @param parent Padre del widget
    VoiceDisplayer(std::string_view modelPath, QWidget *parent = nullptr);

signals:

    /// @brief Transcibe el audio recibido desde un QBuffer
    /// @param buffer Buffer en donde se guarda el audio, debe estan en float
    void transcribeAudio(const QByteArray& buffer);

    /// @brief Método de conveniencia para relanzar resultReady()
    void trasnscriptionDisplayed();

private:

    Susurrador* stt_m;

    QThread workerThread_m;

};

} // namespace My

#endif // VOICEDISPLAYER_H
