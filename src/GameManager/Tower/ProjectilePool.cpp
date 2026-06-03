#include "../../Header/ProjectilePool.hpp"
#include <iostream>

ProjectilePool::ProjectilePool(int size) {  //initialise pool size 
    // Standby : Chargement de la texture (décommenter quand les sprites seront prêts)
    /*
    if (!projectileTexture.loadFromFile("../Sprite/Projectile.png")) {
        std::cout << "Erreur de chargement de la texture Projectile.png" << std::endl;
    }
    */

    pool.resize(size);
    for (int i = 0; i < size; ++i) {
        pool[i].Deactivate();
        // pool[i].sprite.setTexture(projectileTexture); // Standby
    }
}


Projectile* ProjectilePool::acquireProjectile() {
    for (auto& projectile : pool) {
        if (!projectile.IsActive) {
            return &projectile;
        }
    }
    return nullptr;
}

void ProjectilePool::UpdateAll(float deltaTime) {
    for (auto& projectile : pool) {
        if (projectile.IsActive) {
            projectile.UpdatePos(deltaTime);
        }
    }
}

void ProjectilePool::DrawAll(sf::RenderWindow& window) { //Draw projectile if active
    for (auto& projectile : pool) {
        if (projectile.IsActive) {
            projectile.Draw(window);
        }
    }
}