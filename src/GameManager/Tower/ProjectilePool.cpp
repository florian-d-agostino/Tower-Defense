#include "../../Header/ProjectilePool.hpp"
#include <iostream>

ProjectilePool::ProjectilePool(int size) {  // pool size
    // texture (soon)





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

void ProjectilePool::DrawAll(sf::RenderWindow& window)


{ // draw
    for (auto& projectile : pool) {
        if (projectile.IsActive) {
            projectile.Draw(window);
        }
    }
}