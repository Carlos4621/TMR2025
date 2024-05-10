#include "BufferVoiceRecorder.h"

namespace My {

BufferVoiceRecorder::BufferVoiceRecorder(const QAudioDevice &device, const QAudioFormat &format, QObject *parent)
    : QObject{parent} {

    if (!device.isFormatSupported(format)) {
        throw std::runtime_error{ "Format not supported in the device selected" };
    }

    source_m = new QAudioSource{ device, format };
}

void BufferVoiceRecorder::start() {
    if (isRecording) {
        return;
    }

    buffer_m.reset();
    buffer_m.open(QIODevice::WriteOnly);
    source_m->start(&buffer_m);

    isRecording = true;
}

void BufferVoiceRecorder::stop() {
    if (!isRecording) {
        return;
    }

    buffer_m.close();
    source_m->stop();

    isRecording = false;
}

const QBuffer& BufferVoiceRecorder::getBuffer() const noexcept {
    return buffer_m;
}

} // namespace My
