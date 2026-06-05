#include "../Header/GameManager.hpp"
#include "../Header/Menu.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Definition of the global pointer
GameManager* g_gameManager = nullptr;

GameManager::GameManager() 
    : m_baseHp(20), 
    m_gold(100), 
    m_ennemyManager(100),
    m_projectilePool(100),
    m_passiveGoldTimer(0.0f)
{
    g_gameManager = this; // Store reference to this active instance
    loadLevel("data/lvl/lvl1.json");
    m_ennemyManager.setPath(m_path);
}

bool GameManager::loadLevel(const std::string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier de niveau: " << filepath << endl;
        return false;
    }

    // Read entire file content
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    file.close();

    // 1. Parse map_name
    size_t namePos = content.find("\"map_name\"");
    if (namePos != string::npos) {
        size_t startQuote = content.find("\"", namePos + 10);
        size_t endQuote = content.find("\"", startQuote + 1);
        m_mapName = content.substr(startQuote + 1, endQuote - startQuote - 1);
    } else {
        m_mapName = "Niveau Sans Nom";
    }

    // 2. Parse paths (waypoints)
    m_path.clear();
    size_t pathPos = content.find("\"paths\"");
    size_t gridPos = content.find("\"grid\"");
    if (pathPos != string::npos && gridPos != string::npos) {
        size_t cur = pathPos;
        while ((cur = content.find("{\"x\"", cur)) != string::npos && cur < gridPos) {
            // Find x value
            cur = content.find(":", cur);
            int gx = stoi(content.substr(cur + 1));
            
            // Find y value
            cur = content.find("\"y\"", cur);
            cur = content.find(":", cur);
            int gy = stoi(content.substr(cur + 1));
            
            // Convert grid (20x15) to pixels (1200x800)
            // grid width = 20 -> cell_w = 60
            // grid height = 15 -> cell_h = 53.333f
            float px = gx * 60.f + 30.f;
            float py = gy * 53.333f + 26.666f;
            m_path.push_back({px, py});
        }
    }

    // 3. Parse grid
    m_grid.assign(15, vector<int>(20, 0));
    if (gridPos != string::npos) {
        size_t cur = content.find("[", gridPos);
        int row = 0;
        int col = 0;
        // Skip the very first opening bracket of the 2D grid array
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

void GameManager::handleEvents(sf::RenderWindow& window, Menu& menu) {
    while (const std::optional event = window.pollEvent()) {
        // Handle window close
        if (event->is<sf::Event::Closed>()) {
            menu.setState(MenuState::Exit);
            window.close();
        }

        // Adjust view boundaries on window resize
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
            window.setView(sf::View(visibleArea));
        }

        // Mouse button pressed events
        if (const auto* press = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (press->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(press->position);
                int gx = static_cast<int>(mousePos.x / 60.f);
                int gy = static_cast<int>(mousePos.y / 53.33f);

                if (gx >= 0 && gx < 20 && gy >= 0 && gy < 15) {
                    if (m_grid[gy][gx] == 0 && m_gold >= 50) {
                        m_gold -= 50;
                        m_grid[gy][gx] = 2; // Mark as occupied
                        m_towers.push_back({sf::Vector2f(gx * 60.f + 30.f, gy * 53.33f + 26.66f)});
                    }
                }
            }
        }

        // Key pressed events
        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPress->code == sf::Keyboard::Key::Space) {
                // Start a wave of 10 enemies
                m_ennemyManager.spawn(10, m_path[0]);
            }
            else if (keyPress->code == sf::Keyboard::Key::Escape) {
                // Exit gameplay and return to the main menu
                menu.setState(MenuState::MainMenu);
            }
        }
    }
}

void GameManager::update(float deltaTime) {
    // 1. Update enemies
    m_ennemyManager.update(deltaTime);

    // 2. Update active projectiles
    m_projectilePool.UpdateAll(deltaTime);

    // 3. Update towers and handle shooting
    vector<Ennemy*> activeEnnemies = m_ennemyManager.getActiveEnnemies();
    for (auto& tower : m_towers) {
        if (tower.fireTimer > 0.0f) {
            tower.fireTimer -= deltaTime;
        }

        if (tower.fireTimer <= 0.0f) {
            // Find the first enemy in range
            Ennemy* target = nullptr;
            for (auto* enemy : activeEnnemies) {
                Vector2D towerPos2D(tower.pos.x, tower.pos.y);
                if (towerPos2D.distance(enemy->pos) <= tower.range) {
                    target = enemy;
                    break; // Target found
                }
            }

            if (target != nullptr) {
                // Get a projectile from the pool
                Projectile* proj = m_projectilePool.acquireProjectile();
                if (proj != nullptr) {
                    // Compute direction and velocity towards target
                    Vector2D towerPos2D(tower.pos.x, tower.pos.y);
                    Vector2D direction = (target->pos - towerPos2D).normalized();
                    float bulletSpeed = 300.f; // Speed in pixels/second
                    Vector2D velocity = direction * bulletSpeed;

                    // Shoot bullet (deals 25 damage)
                    proj->Activate(25, towerPos2D, velocity, target);

                    // Reset tower cooldown
                    tower.fireTimer = tower.fireCooldown;
                }
            }
        }
    }
    // 4. Passive gold generation (2 gold every 1 second)
    m_passiveGoldTimer += deltaTime;
    if (m_passiveGoldTimer >= 1.0f) {
        m_gold += 2;
        m_passiveGoldTimer = 0.0f;
    }
}

void GameManager::addGold(int amount) {
    m_gold += amount;
}

