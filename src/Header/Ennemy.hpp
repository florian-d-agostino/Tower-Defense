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





    ////// EN STAND BY CONSTRUCTIO EN COURS //////

        // Récupère un pointeur vers un ennemi libre (inactif)
    Ennemy* acquireEnnemy();
    
    // Accesseur pour obtenir le pool (utile pour faire les boucles d'update/draw)
    std::vector<Ennemy>& getPool();
};
#endif // ENNEMY_HPP
