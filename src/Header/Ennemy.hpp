#ifndef ENNEMY_HPP
#define ENNEMY_HPP
#include <vector>

// pos/speed 
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




    // sprite (En attente)
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

    // add
    Ennemy* acquireEnnemy();

    // get pool
    std::vector<Ennemy>& getPool();
};
#endif
