#include "SoundManager.hpp"
#include <iostream>
#include <algorithm>

SoundManager::SoundManager() : m_muted(false) {}

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::toggleMute() {
    m_muted = !m_muted;

    // Apply mute state to background music
    if (m_muted) {
        m_music.setVolume(0.f);
    } else {
        m_music.setVolume(100.f);
    }

    // Apply mute state to all playing sounds
    for (auto& sound : m_sounds) {
        if (m_muted) {
            sound.setVolume(0.f);
        } else {
            sound.setVolume(100.f);
        }
    }
}

bool SoundManager::isMuted() const {
    return m_muted;
}

void SoundManager::playMusic(const std::string& filepath, bool loop) {
    // Attempt to open music stream
    if (!m_music.openFromFile(filepath)) {
        std::cerr << "Warning: Could not open music file: " << filepath << std::endl;
        return;
    }

    m_music.setLooping(loop);
    
    // Set appropriate volume
    if (m_muted) {
        m_music.setVolume(0.f);
    } else {
        m_music.setVolume(100.f);
    }

    m_music.play();
}

void SoundManager::stopMusic() {
    m_music.stop();
}

void SoundManager::playSound(const std::string& filepath) {
    // Lazy-load sound buffer into memory if not loaded yet
    if (m_buffers.find(filepath) == m_buffers.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filepath)) {
            std::cerr << "Warning: Could not load sound effect file: " << filepath << std::endl;
            return;
        }
        m_buffers[filepath] = buffer;
    }

    // Spawn sound instance and bind loaded buffer (SFML 3 constructor requires buffer)
    sf::Sound sound(m_buffers[filepath]);
    
    if (m_muted) {
        sound.setVolume(0.f);
    } else {
        sound.setVolume(100.f);
    }

    sound.play();

    // Store sound to keep it alive during playback
    m_sounds.push_back(sound);
}

void SoundManager::update() {
    // Remove stopped sounds to recycle audio channels
    m_sounds.erase(
        std::remove_if(m_sounds.begin(), m_sounds.end(),
            [](const sf::Sound& s) { return s.getStatus() == sf::Sound::Status::Stopped; }),
        m_sounds.end()
    );
}
