#ifndef ENNEMY_HPP
#define ENNEMY_HPP
#include <vector>

// Position and speed 
#include "Vector2D.hpp" 






class Ennemy {
    public: 
    int pv;
    Vector2D velocity;
    bool alive;
    Vector2D pos;



    // Constructor
    Ennemy();


    // Spawn ennemy
    void spawn(Vector2D startPos);


    // Update position
    void updatePos();


    // Take damage;
    void takeDamage(int damage);


    // Deat
    void death();


    // Draw
    void draw();
}






class EnnemyPool {
    private:
    vector<Ennemy> pool;
    int poolSize;


    public:
    EnnemyPool(int size);

    // add ennemy
    Ennemy* acquireEnnemy();


    // get all the ennemies
    std::vector<Ennemy>& getPool();
};
#endif
