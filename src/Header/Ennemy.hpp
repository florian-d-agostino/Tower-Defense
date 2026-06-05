#ifndef ENNEMY_HPP
#define ENNEMY_HPP
#include <vector>

// Position and speed 
#include "Vector2D.hpp" 

namespace sf {
    class RenderWindow;
}

class Ennemy {
    public: 
    int hp;
    Vector2D velocity;
    bool alive;
    Vector2D pos;
    int currentWaypointIndex;

    // Standby: sprite pour implémentation future
    // sf::Sprite sprite;

    // Constructor
    Ennemy();

    
    void spawn(Vector2D startPos);
    
    void updatePos(float deltaTime);
    
    void takeDamage(int damage);
    
    void death();
    
    void draw(sf::RenderWindow& window);
};

class EnnemyPool {
    private:
    std::vector<Ennemy> pool;

    public:
    EnnemyPool(int size);

    // add ennemy
    Ennemy* acquireEnnemy();

    // get all the ennemies
    std::vector<Ennemy>& getPool();
};
#endif
