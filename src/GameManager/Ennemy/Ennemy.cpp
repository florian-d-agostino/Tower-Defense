#include "../../Header/Ennemy.hpp"
#include <iostream>

using namespace std;





// Init ennemy
Ennemy::Ennemy() {
    pv = 100;
    pos = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    alive = false;
    currentWaypointIndex = 0;
}




// Spawn ennemy ----- Stand By pas fini !----
void Ennemy::spawn(Vector2D startPos){
    pos = startPos;
    pv = 100;
    velocity = {1.0f, 0.0f};
    alive = true;
}



// Update position
void Ennemy::updatePos(){
    if (!alive) return;
    pos.x += velocity.x;
    pos.y += velocity.y;
}




// If take damage
void Ennemy::takeDamage(int damage) {
    if (!alive) return;

    pv -= damage;
    if (pv <= 0) {
        death();
    }
}



// Death
void Ennemy::death() {
    alive = false;
    cout << "Ennemy mort !" << endl;
}


void Ennemy::draw(){
    if (!alive) return;
    
}
