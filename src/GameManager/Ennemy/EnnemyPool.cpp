#include "../../Header/Ennemy.hpp"



// Constructor
EnnemyPool::EnnemyPool(int size) {
    pool.resize(size);
}




// Acquire an ennemy from the pool
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