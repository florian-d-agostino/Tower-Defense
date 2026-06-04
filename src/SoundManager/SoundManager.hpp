#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <vector>

// Singleton manager for game music and sound effects
class SoundManager {
private:
    bool m_muted;
    sf::Music m_music;
    std::map<std::string, sf::SoundBuffer> m_buffers;
    std::vector<sf::Sound> m_sounds;

    SoundManager(); // Private constructor for Singleton

public:
    static SoundManager& getInstance();

    // Sound toggle control
    void toggleMute();
    bool isMuted() const;

    // Music operations
    void playMusic(const std::string& filepath, bool loop = true);
    void stopMusic();

    // Sound effect operations
    void playSound(const std::string& filepath);
    void update();
};

#endif
