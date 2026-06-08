#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Vector2D.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <optional>

class Ennemy; // forward declaration

class Projectile {
public:
    int damage;
    Vector2D pos;
    Vector2D velocity;


    // Target
    Ennemy* target;


    bool IsActive;
    float lifetime;
    
    // sprite
    std::optional<sf::Sprite> sprite;

    Projectile();
    Projectile(int damage, Vector2D pos, Vector2D velocity, Ennemy* target, bool IsActive);

    void UpdatePos(float deltaTime); 
    void Draw(sf::RenderWindow& window);
    
    // methods
    void Activate(int damage, Vector2D startPos, Vector2D startVelocity, Ennemy* target);
    void Deactivate();
};

#endif
