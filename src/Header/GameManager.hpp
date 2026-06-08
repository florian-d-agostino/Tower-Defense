#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "EnnemyManager.hpp"
#include "Vector2D.hpp"
#include "Tower.hpp"
#include "ProjectilePool.hpp"

class Menu;
class GameRenderer;

extern class GameManager* g_gameManager;

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

    // Timer
    float m_passiveGoldTimer; 



    bool loadLevel(const std::string& filepath);

public:
    GameManager();



    // methods
    void handleEvents(sf::RenderWindow& window, Menu& menu);
    void update(float deltaTime);
    void addGold(int amount);
};

#endif 
