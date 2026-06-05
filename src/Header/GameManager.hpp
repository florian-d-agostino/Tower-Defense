#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "EnnemyManager.hpp"
#include "Vector2D.hpp"
#include "Tower.hpp"
#include "ProjectilePool.hpp"

class Menu; // Forward declaration
class GameRenderer; // Forward declaration

extern class GameManager* g_gameManager; // Pointeur global pour l'accès facile

class GameManager {
    friend class GameRenderer;

private:
    int m_baseHp;
    int m_gold;
    EnnemyManager m_ennemyManager;
    std::vector<Vector2D> m_path;
    std::vector<std::vector<int>> m_grid;
    std::string m_mapName;
    std::vector<Tower> m_towers;
    ProjectilePool m_projectilePool;
    float m_passiveGoldTimer; // Timer pour l'or automatique

    bool loadLevel(const std::string& filepath);

public:
    GameManager();

    // Event handling and layout update
    void handleEvents(sf::RenderWindow& window, Menu& menu);
    void update(float deltaTime);
    void addGold(int amount);
};

#endif // GAME_MANAGER_HPP
