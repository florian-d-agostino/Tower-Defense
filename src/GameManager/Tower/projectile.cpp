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
}

Projectile::Projectile(int damage, Vector2D pos, Vector2D velocity, Ennemy* target, bool IsActive) {
    this->damage = damage;
    this->pos = pos;
    this->velocity = velocity;
    this->target = target;
    this->IsActive = IsActive;
} 

void Projectile::UpdatePos(float deltaTime) {
    if (!IsActive) return;
    
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
    
    sprite.setPosition(pos.x, pos.y);

    if (target != nullptr && target->alive) {
        float dx = target->pos.x - pos.x;
        float dy = target->pos.y - pos.y;
        float distance = std::sqrt(dx*dx + dy*dy);
        
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
}

void Projectile::Deactivate() {
    IsActive = false;
}