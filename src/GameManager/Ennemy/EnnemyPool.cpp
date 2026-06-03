#include "../../Header/Ennemy.hpp"

EnnemyPool::EnnemyPool(int size) : poolSize(size) {
    pool.resize(size);
}

Ennemy* EnnemyPool::acquireEnnemy() {
    for (int i = 0; i < poolSize; ++i) {
        if (!pool[i].alive) {
            return &pool[i];
        }
    }
    return nullptr;
}

std::vector<Ennemy>& EnnemyPool::getPool() {
    return pool;
}