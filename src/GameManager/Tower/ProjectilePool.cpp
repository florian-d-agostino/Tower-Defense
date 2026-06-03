#include "../../Header/ProjectilePool.hpp"

// Constructeur : initialise la pool avec un certain nombre de projectiles inactifs
ProjectilePool::ProjectilePool(int size) {
    pool.resize(size);
    for (int i = 0; i < size; ++i) {
        pool[i].Deactivate();
    }
}

// Cherche un projectile inactif dans la pool et renvoie un pointeur vers lui
// (Renvoie nullptr si tous les projectiles sont déjà actifs)
Projectile* ProjectilePool::acquireProjectile() {
    for (auto& projectile : pool) {
        if (!projectile.IsActive) {
            return &projectile;
        }
    }
    return nullptr;
}

// Met à jour la physique et les collisions de tous les projectiles qui sont en train de voler
void ProjectilePool::UpdateAll(float deltaTime) {
    for (auto& projectile : pool) {
        if (projectile.IsActive) {
            projectile.UpdatePos(deltaTime);
        }
    }
}

// Affiche tous les projectiles en vol à l'écran
void ProjectilePool::DrawAll(sf::RenderWindow& window) {
    for (auto& projectile : pool) {
        if (projectile.IsActive) {
            projectile.Draw(window);
        }
    }
}