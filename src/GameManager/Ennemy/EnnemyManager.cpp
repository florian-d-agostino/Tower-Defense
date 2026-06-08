#include "../../Header/EnnemyManager.hpp"
#include <iostream>


using namespace std;

EnnemyManager::EnnemyManager(int poolSize): 
    pool(poolSize), 
    enemiesToSpawn(0), 
    spawnTimer(0.0f), 
    spawnInterval(1.0f), 
    enemySpeed(100.0f), 
    spawnPos(0.0f, 0.0f) {}



void EnnemyManager::setPath(const vector<Vector2D>& newPath) {
    path = newPath;
}



void EnnemyManager::spawn(int amount, Vector2D pos) {
    enemiesToSpawn = amount;
    spawnPos = pos;



    // Spawn Timer
    spawnTimer = spawnInterval;
    cout << "Wave started: spawning " << amount << " enemies at position (" << pos.x << ", " << pos.y << ")" << endl;
}



// Position ennemies update
void EnnemyManager::update(float deltaTime) {



    // Wave Logic
    if (enemiesToSpawn > 0) {
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            Ennemy* enemy = pool.acquireEnnemy();
            if (enemy != nullptr) {
                enemy->spawn(spawnPos);
                enemy->currentWaypointIndex = 0;


                // Movement
                if (path.size() > 1) {
                    Vector2D direction = (path[1] - path[0]).normalized();
                    enemy->velocity = direction * enemySpeed;
                }


                // Countdown to next spawn
                cout << "Spawned enemy from pool! Remaining to spawn: " << (enemiesToSpawn - 1) << endl;
                enemiesToSpawn -= 1;
                spawnTimer = 0.0f;
            }
        }
    }



    // Update active ennemy
    vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        Ennemy& enemy = enemies[i];
        if (enemy.alive) {
            enemy.updatePos(deltaTime);



            // Check next waypoint
            int nextWaypointIndex = enemy.currentWaypointIndex + 1;
            if (nextWaypointIndex < static_cast<int>(path.size())) {
                float dist = enemy.pos.distance(path[nextWaypointIndex]);
                float speed = enemy.velocity.length();





                // Ennemies speed update
                float movementThisFrame = speed * deltaTime;
                if (dist <= movementThisFrame || dist < 0.1f) {
                    enemy.pos = path[nextWaypointIndex];
                    enemy.currentWaypointIndex = nextWaypointIndex;


                    int targetWaypointIndex = nextWaypointIndex + 1;
                    if (targetWaypointIndex < static_cast<int>(path.size())) {
                        Vector2D direction = (path[targetWaypointIndex] - path[nextWaypointIndex]).normalized();
                        enemy.velocity = direction * speed;
                        cout << "Enemy reached waypoint " << nextWaypointIndex << ", heading to " << targetWaypointIndex << endl;
                    } else {


                        // When Base is attacked
                        enemy.death();
                        cout << "An enemy attacked the base!" << endl;


                    }
                }
            } else {
                enemy.alive = false;
            }
        }
    }
}

void EnnemyManager::draw(sf::RenderWindow& window) {
    vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].alive) {
            enemies[i].draw(window);
        }
    }
}

vector<Ennemy*> EnnemyManager::getActiveEnnemies() {
    vector<Ennemy*> activeEnnemies;
    vector<Ennemy>& enemies = pool.getPool();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i].alive) {
            activeEnnemies.push_back(&enemies[i]);
        }
    }
    return activeEnnemies;
}
