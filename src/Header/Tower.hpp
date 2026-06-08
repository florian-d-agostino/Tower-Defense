#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

struct Tower {
    sf::Vector2f pos;
    float range = 150.f;
    float fireCooldown = 1.0f;
    float fireTimer = 0.0f;
};

#endif
