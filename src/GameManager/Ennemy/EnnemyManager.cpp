#include "../../Header/EnnemyManager.hpp"
#include <iostream>




EnnemyManager::EnnemyManager(int poolSize) 
    : pool(poolSize), 
    enemiesToSpawn(0), 
    spawnTimer(0.0f), 
    spawnInterval(1.0f), 
    enemySpeed(2.0f), 
    spawnPos(0.0f, 0.0f) {}



void EnnemyManager::setPath(const std::vector<Vector2D>& newPath) {
    path = newPath;
}



void EnnemyManager::spawn(int amount, Vector2D pos) {
    enemiesToSpawn = amount;
    spawnPos = pos;


    // Set spawnTimer to spawnInterval so the first enemy spawns immediately on the next update
    spawnTimer = spawnInterval;
    std::cout << "Wave started: spawning " << amount << " enemies at position (" << pos.x << ", " << pos.y << ")" << std::endl;
}

void EnnemyManager::update(float deltaTime) {


    // Wave Logic
    if (enemiesToSpawn > 0) {
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            Ennemy* enemy = pool.acquireEnnemy();
            if (enemy != nullptr) {
                enemy->spawn(spawnPos);
                enemy->currentWaypointIndex = 0;
                
                // If we have a path, direct the enemy to the first waypoint (index 1)
                if (path.size() > 1) {
                    Vector2D direction = (path[1] - path[0]).normalized();
                    enemy->velocity = direction * enemySpeed;
                }
                
                std::cout << "Spawned enemy from pool! Remaining to spawn: " << (enemiesToSpawn - 1) << std::endl;
                enemiesToSpawn--;
                spawnTimer = 0.0f;
            }
        }
    }





    // Update active ennemy
    std::vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        Ennemy& enemy = enemies[i];
        if (enemy.alive) {
            enemy.updatePos(deltaTime);

            // Check if we reached the next waypoint
            int nextWaypointIndex = enemy.currentWaypointIndex + 1;
            if (nextWaypointIndex < static_cast<int>(path.size())) {
                float dist = enemy.pos.distance(path[nextWaypointIndex]);
                float speed = enemy.velocity.length();

                // If close enough to the waypoint, snap to it and direct to the next waypoint
                float movementThisFrame = speed * deltaTime;
                if (dist <= movementThisFrame || dist < 0.1f) {
                    enemy.pos = path[nextWaypointIndex];
                    enemy.currentWaypointIndex = nextWaypointIndex;

                    int targetWaypointIndex = nextWaypointIndex + 1;
                    if (targetWaypointIndex < static_cast<int>(path.size())) {
                        Vector2D direction = (path[targetWaypointIndex] - path[nextWaypointIndex]).normalized();
                        enemy.velocity = direction * speed;
                        std::cout << "Enemy reached waypoint " << nextWaypointIndex << ", heading to " << targetWaypointIndex << std::endl;
                    } else {
                        // Reached the end of the path!
                        enemy.death(); // Sets alive = false
                        std::cout << "An enemy reached the end of the path! Base took damage." << std::endl;
                        // Future hook: GameManager::getInstance().takeDamage(1);
                    }
                }
            } else {
                // Out of waypoints, deactivate just in case
                enemy.alive = false;
            }
        }
    }
}

void EnnemyManager::draw(sf::RenderWindow& window) {
    std::vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].alive) {
            enemies[i].draw(window);
        }
    }
}

std::vector<Ennemy*> EnnemyManager::getActiveEnnemies() {
    std::vector<Ennemy*> activeEnnemies;
    std::vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].alive) {
            activeEnnemies.push_back(&enemies[i]);
        }
    }
    return activeEnnemies;
}
