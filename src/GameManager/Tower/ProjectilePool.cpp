#include "../../Header/ProjectilePool.hpp"
#include <iostream>

using namespace std;

ProjectilePool::ProjectilePool(int size) {
    // 1. On charge la texture UNE SEULE FOIS pour tout le jeu
    if (!projectileTexture.loadFromFile("../Sprite/Projectile.png")) {
        cout << "Erreur de chargement de la texture Projectile.png" << endl;
    }

    // 2. On remplit la pool avec des projectiles inactifs
    pool.resize(size);
    for (int i = 0; i < size; i++) {
        // On donne la texture chargée au sprite de chaque projectile
        pool[i].sprite.setTexture(projectileTexture);
    }
}

Projectile* ProjectilePool::acquireProjectile() {
    for (int i = 0; i < pool.size(); i++) {
        if (!pool[i].IsActive) {
            return &pool[i];
        }
    }
    return nullptr; // Plus de projectiles dispos !
}

void ProjectilePool::UpdateAll(float deltaTime) {
    for (int i = 0; i < pool.size(); i++) {
        if (pool[i].IsActive) {
            pool[i].UpdatePos(deltaTime);
        }
    }
}

void ProjectilePool::DrawAll(sf::RenderWindow& window) {
    for (int i = 0; i < pool.size(); i++) {
        if (pool[i].IsActive) {
            pool[i].Draw(window);
        }
    }
}