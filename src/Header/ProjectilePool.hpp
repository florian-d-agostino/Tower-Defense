#ifndef PROJECTILEPOOL_HPP
#define PROJECTILEPOOL_HPP

#include "Projectile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class ProjectilePool {
private:
    std::vector<Projectile> pool;
    sf::Texture projectileTexture;

public:
    // constructor
    ProjectilePool(int size);

    // get projectile
    Projectile* acquireProjectile();

    // update all
    void UpdateAll(float deltaTime);

    // draw all
    void DrawAll(sf::RenderWindow& window);
};

#endif
