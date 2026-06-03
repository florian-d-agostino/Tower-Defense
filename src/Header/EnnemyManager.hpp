#ifndef ENNEMY_MANAGER_HPP
#define ENNEMY_MANAGER_HPP

#include "Ennemy.hpp"
#include "Vector2D.hpp"
#include <vector>

// Forward declaration of SFML RenderWindow
namespace sf {
    class RenderWindow;
}

class EnnemyManager {
private:
    EnnemyPool pool;
    std::vector<Vector2D> path;
    
    // Wave spawning state
    int enemiesToSpawn;
    float spawnTimer;
    float spawnInterval;
    float enemySpeed;
    Vector2D spawnPos;

public:
    // Constructor
    EnnemyManager(int poolSize);
    
    // Set the path that enemies should follow
    void setPath(const std::vector<Vector2D>& newPath);
    
    // Start spawning a wave of enemies at the specified position
    void spawn(int amount, Vector2D pos);

    // Update all active enemies and wave spawning
    void update(float deltaTime);

    // Render all active enemies
    void draw(sf::RenderWindow& window);

    // Get list of active enemies (useful for tower targeting)
    std::vector<Ennemy*> getActiveEnnemies();
};

#endif // ENNEMY_MANAGER_HPP
