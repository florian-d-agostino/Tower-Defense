#include "../../Header/Ennemy.hpp"
#include <iostream>

using namespace std;





// Init ennemy
Ennemy::Ennemy() {
    hp = 100;
    pos = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    alive = false;
    currentWaypointIndex = 0;
}




// Spawn ennemy ----- Stand By pas fini !----
void Ennemy::spawn(Vector2D startPos){
    pos = startPos;
    hp = 100;
    velocity = {1.0f, 0.0f};
    alive = true;
}



// Update position
void Ennemy::updatePos(float deltaTime){
    if (!alive) return;
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
}




// If take damage
void Ennemy::takeDamage(int damage) {
    if (!alive) return;

    hp -= damage;
    if (hp <= 0) {
        death();
    }
}



// Death
void Ennemy::death() {
    alive = false;
    cout << "Enemy died!" << endl;
}


void Ennemy::draw(sf::RenderWindow& window){
    if (!alive) return;
    
}
