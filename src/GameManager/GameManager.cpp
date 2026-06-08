#include "../Header/GameManager.hpp"
#include "../Header/Menu.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;



// Pointers
GameManager* g_gameManager = nullptr;

GameManager::GameManager() 
    : m_baseHp(20), 
    m_gold(100), 
    m_ennemyManager(100),
    m_projectilePool(100),
    m_passiveGoldTimer(0.0f)
{
    g_gameManager = this;
    loadLevel("data/lvl/lvl1.json");
    m_ennemyManager.setPath(m_path);
}




bool GameManager::loadLevel(const std::string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier de niveau: " << filepath << endl;
        return false;
    }




    // read file
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    file.close();





    // map name
    size_t namePos = content.find("\"map_name\"");
    if (namePos != string::npos) {
        size_t startQuote = content.find("\"", namePos + 10);
        size_t endQuote = content.find("\"", startQuote + 1);
        m_mapName = content.substr(startQuote + 1, endQuote - startQuote - 1);
    } else {
        m_mapName = "Niveau Sans Nom";
    }




    // paths
    m_path.clear();
    size_t pathPos = content.find("\"paths\"");
    size_t gridPos = content.find("\"grid\"");
    if (pathPos != string::npos && gridPos != string::npos) {
        size_t cur = pathPos;
        while ((cur = content.find("{\"x\"", cur)) != string::npos && cur < gridPos) {



            // coord x
            cur = content.find(":", cur);
            int gx = stoi(content.substr(cur + 1));


            // coord y
            cur = content.find("\"y\"", cur);
            cur = content.find(":", cur);
            int gy = stoi(content.substr(cur + 1));




            // grid to pixels
            float px = gx * 60.f + 30.f;
            float py = gy * 53.333f + 26.666f;
            m_path.push_back({px, py});
        }
    }





    // grid
    m_grid.assign(15, vector<int>(20, 0));
    if (gridPos != string::npos) {
        size_t cur = content.find("[", gridPos);
        int row = 0;
        int col = 0;



        // grid reader
        if (cur != string::npos) cur++; 
        
        while (cur < content.size() && row < 15) {
            char c = content[cur];
            if (c == '[') {
                col = 0;
            } else if (c == ']') {
                row++;
            } else if (isdigit(c)) {
                int val = c - '0';
                if (col < 20 && row < 15) {
                    m_grid[row][col] = val;
                    col++;
                }
            }
            cur++;
        }
    }

    return true;
}



// Events
void GameManager::handleEvents(sf::RenderWindow& window, Menu& menu) {
    while (const std::optional event = window.pollEvent()) {


        // close
        if (event->is<sf::Event::Closed>()) {
            menu.setState(MenuState::Exit);
            window.close();
        }


        // mouse click
        if (const auto* press = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (press->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(press->position);
                int gx = static_cast<int>(mousePos.x / 60.f);
                int gy = static_cast<int>(mousePos.y / 53.33f);




                if (gx >= 0 && gx < 20 && gy >= 0 && gy < 15) {
                    if (m_grid[gy][gx] == 0 && m_gold >= 50) {
                        m_gold -= 50;
                        m_grid[gy][gx] = 2;
                        m_towers.push_back({sf::Vector2f(gx * 60.f + 30.f, gy * 53.33f + 26.66f)});
                    }
                }
            }
        }




        // keyboard spacebar
        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPress->code == sf::Keyboard::Key::Space) {
                m_ennemyManager.spawn(10, m_path[0]);
            }
            else if (keyPress->code == sf::Keyboard::Key::Escape) {


                // back to menu
                menu.setState(MenuState::MainMenu);
            }
        }
    }
}

void GameManager::update(float deltaTime) {


    // update enemies
    m_ennemyManager.update(deltaTime);



    // update projectiles
    m_projectilePool.UpdateAll(deltaTime);



    // update towers and shooting
    vector<Ennemy*> activeEnnemies = m_ennemyManager.getActiveEnnemies();
    for (auto& tower : m_towers) {
        if (tower.fireTimer > 0.0f) {
            tower.fireTimer -= deltaTime;
        }

        if (tower.fireTimer <= 0.0f) {


            // enemy in range
            Ennemy* target = nullptr;
            for (auto* enemy : activeEnnemies) {
                Vector2D towerPos2D(tower.pos.x, tower.pos.y);
                if (towerPos2D.distance(enemy->pos) <= tower.range) {
                    target = enemy;
                    break;
                }
            }




            if (target != nullptr) {

                // get projectile
                Projectile* proj = m_projectilePool.acquireProjectile();


                if (proj != nullptr) {
                    // calculate speed
                    Vector2D towerPos2D(tower.pos.x, tower.pos.y);
                    Vector2D direction = (target->pos - towerPos2D).normalized();
                    float bulletSpeed = 300.f;
                    Vector2D velocity = direction * bulletSpeed;

                    // shoot
                    proj->Activate(25, towerPos2D, velocity, target);

                    // reset cooldown
                    tower.fireTimer = tower.fireCooldown;
                }
            }
        }
    }



    // passive gold regen
    m_passiveGoldTimer += deltaTime;
    if (m_passiveGoldTimer >= 1.0f) {
        m_gold += 2;
        m_passiveGoldTimer = 0.0f;
    }
}

// add gold when kill
void GameManager::addGold(int amount) {
    m_gold += amount;
}

