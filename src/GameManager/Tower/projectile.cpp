#include <iostream>
#include "../../Header/Projectile.hpp"


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

    cout << "pos = [" << pos.x << ", " << pos.y << "]" << endl;
}

void Projectile::Draw() {
    if (IsActive) {
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
    if (pos.x == target->pos.x && pos.y == target->pos.y ) {
        target->takedamage(this.damage);    
        this->IsActive = false;
    }
}