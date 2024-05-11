#pragma once

#include <SDL_audio.h>

class sound {
    
private:
    SDL_AudioSpec m_wavSpec;
    Uint32 m_wavLength;
    Uint8* m_wavBuffer;
    SDL_AudioDeviceID m_deviceId;
    bool m_isLoaded;
    
public:
    explicit sound(const char* filename) : m_wavBuffer(nullptr), m_wavLength(0), m_deviceId(0) {
        m_wavSpec = {};
        if (SDL_LoadWAV(filename, &m_wavSpec, &m_wavBuffer, &m_wavLength) == nullptr) {
            m_isLoaded = false;
        } else {
            m_isLoaded = true;
        }
    }

    ~sound() {
        if (m_isLoaded) {
            SDL_FreeWAV(m_wavBuffer);
            SDL_CloseAudioDevice(m_deviceId);
        }
    }

    bool load() const;
    void play();
    void play_loop();

};