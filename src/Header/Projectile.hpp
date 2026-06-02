#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Vector2D.hpp"
#include <cmath>

class Ennemy; // Forward declaration pour éviter les inclusions circulaires

class Projectile {
public:
    int damage;
    Vector2D pos;
    Vector2D velocity;
    Ennemy* target; // Pointeur vers l'ennemi visé
    bool IsActive;

    Projectile();
    Projectile(int damage, Vector2D pos, Vector2D velocity, Ennemy* target, bool IsActive);

    void UpdatePos(float deltaTime); 
    void Draw();
    
    // Méthode pour "recycler" le projectile sorti de la pool
    void Activate(int damage, Vector2D startPos, Vector2D startVelocity, Ennemy* target);
    void Deactivate();
};

#endif
