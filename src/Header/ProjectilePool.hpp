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
    // Constructeur : initialise la pool avec un certain nombre de projectiles inactifs
    ProjectilePool(int size);

    // Cherche un projectile inactif dans la pool et renvoie un pointeur vers lui
    // (Renvoie nullptr si tous les projectiles sont déjà actifs)
    Projectile* acquireProjectile();

    // Met à jour la physique et les collisions de tous les projectiles qui sont en train de voler
    void UpdateAll(float deltaTime);

    // Affiche tous les projectiles en vol à l'écran
    void DrawAll(sf::RenderWindow& window);
};

#endif
