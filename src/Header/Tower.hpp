#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

struct Tower {
    sf::Vector2f pos;
    float range = 150.f;        // Portée de tir (pixels)
    float fireCooldown = 1.0f;  // Temps entre deux tirs (secondes)
    float fireTimer = 0.0f;     // Chronomètre de recharge
};

#endif
