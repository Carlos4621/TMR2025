#include "VoiceDisplayer.h"

namespace My {

VoiceLabel::VoiceLabel(std::string_view modelPath ,QWidget *parent)
    : QTextEdit{parent}
    , stt_m{modelPath}
{
    setReadOnly(true);
    setFocusPolicy(Qt::NoFocus);
}

void VoiceLabel::transcribeAudio(const QBuffer &buffer) {
    const auto text{ stt_m.manageAudio(buffer) };

    setText(text.c_str());
}

} // namespace My
