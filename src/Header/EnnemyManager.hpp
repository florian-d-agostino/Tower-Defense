#ifndef ENNEMY_MANAGER_HPP
#define ENNEMY_MANAGER_HPP

#include "Ennemy.hpp"
#include "Vector2D.hpp"
#include <vector>

// forward declaration
namespace sf {
    class RenderWindow;
}



class EnnemyManager {
private:
    EnnemyPool pool;
    std::vector<Vector2D> path;
    
    // wave state
    int enemiesToSpawn;
    float spawnTimer;
    float spawnInterval;
    float enemySpeed;
    Vector2D spawnPos;




public:
    // constructor
    EnnemyManager(int poolSize);
    
    // set path
    void setPath(const std::vector<Vector2D>& newPath);
    
    // spawn wave
    void spawn(int amount, Vector2D pos);

    // update
    void update(float deltaTime);

    // draw
    void draw(sf::RenderWindow& window);

    // get active
    std::vector<Ennemy*> getActiveEnnemies();
};

#endif
