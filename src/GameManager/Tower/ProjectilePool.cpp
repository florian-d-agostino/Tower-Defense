#include "../../Header/ProjectilePool.hpp"

ProjectilePool::ProjectilePool(int size) {  //initialise pool size 
    pool.resize(size);
    for (int i = 0; i < size; ++i) {
        pool[i].Deactivate();
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