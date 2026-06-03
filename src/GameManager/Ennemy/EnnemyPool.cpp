#include "../../Header/Ennemy.hpp"

EnnemyPool::EnnemyPool(int size) {
    pool.resize(size);
}

Ennemy* EnnemyPool::acquireEnnemy() {
    for (auto& enemy : pool) {
        if (!enemy.alive) {
            return &enemy;
        }
    }
    return nullptr;
}

std::vector<Ennemy>& EnnemyPool::getPool() {
    return pool;
}