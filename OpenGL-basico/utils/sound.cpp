#include "sound.h"

#include <SDL_timer.h>
#include <thread>

bool sound::load() const {
    return m_isLoaded;
}

void sound::play() {
    if (m_isLoaded) {
        m_deviceId = SDL_OpenAudioDevice(NULL, 0, &m_wavSpec, NULL, 0); // Dispo de audio
        if (m_deviceId == 0) {
            return;
        }
        SDL_QueueAudio(m_deviceId, m_wavBuffer, m_wavLength); // Reproducir el sonido
        SDL_PauseAudioDevice(m_deviceId, 0);
    }
}
