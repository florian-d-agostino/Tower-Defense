#include <iostream>
#include "../../Header/Projectile.hpp"
#include "../../Header/Ennemy.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

Projectile::Projectile() {
    this->damage = 0;
    this->pos = {0.0f, 0.0f};
    this->velocity = {0.0f, 0.0f};
    this->target = nullptr;
    this->IsActive = false;
    this->lifetime = 0.0f;
}

Projectile::Projectile(int damage, Vector2D pos, Vector2D velocity, Ennemy* target, bool IsActive) {
    this->damage = damage;
    this->pos = pos;
    this->velocity = velocity;
    this->target = target;
    this->IsActive = IsActive;
    this->lifetime = 0.0f;
} 

void Projectile::UpdatePos(float deltaTime) {
    if (!IsActive) return;
    
    lifetime += deltaTime;
    if (lifetime > 5.0f) {
        Deactivate();
        return;
    }

    // Homing tracking: orient velocity towards target
    if (target != nullptr && target->alive) {
        Vector2D direction = (target->pos - pos).normalized();
        float speed = velocity.length();
        if (speed > 0.0f) {
            velocity = direction * speed;
        }
    }

    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
    
    sprite.setPosition(pos.x, pos.y);

    if (target != nullptr && target->alive) {
        float distance = pos.distance(target->pos);
        if (distance < 10.0f) {
            target->takeDamage(damage);    
            Deactivate(); 
        }
    }
}

void Projectile::Draw(sf::RenderWindow& window) {
    if (IsActive) {
        window.draw(sprite);
    }
}

void Projectile::Activate(int damage, Vector2D startPos, Vector2D startVelocity, Ennemy* target) {
    this->damage = damage;
    this->pos = startPos;
    this->velocity = startVelocity;
    this->target = target;
    this->IsActive = true;
    this->lifetime = 0.0f;
}

void Projectile::Deactivate() {
    IsActive = false;
}