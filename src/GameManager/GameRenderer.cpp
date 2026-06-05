#include "../Header/GameRenderer.hpp"
#include "../Header/GameManager.hpp"
#include <iostream>

using namespace std;

GameRenderer::GameRenderer() 
    : m_font("data/fonts/segoeui.ttf") {}

void GameRenderer::draw(sf::RenderWindow& window, GameManager& game) {
    // Clear screen
    window.clear(sf::Color(10, 10, 25));

    // Draw the grid cells dynamically
    sf::RectangleShape cell(sf::Vector2f(60.f, 53.33f));
    cell.setOutlineThickness(1.f);
    cell.setOutlineColor(sf::Color(30, 30, 50)); // Subtle grid borders

    for (int r = 0; r < 15; ++r) {
        for (int c = 0; c < 20; ++c) {
            cell.setPosition(sf::Vector2f(c * 60.f, r * 53.33f));
            if (game.m_grid[r][c] == 1) {
                cell.setFillColor(sf::Color(70, 60, 55)); // Grey-brown for path cells
            } else {
                cell.setFillColor(sf::Color(15, 25, 30)); // Very dark green-blue for buildable ground
            }
            window.draw(cell);
        }
    }

    // Draw active enemies
    game.m_ennemyManager.draw(window);

    // Draw placed towers
    sf::CircleShape towerShape(12.f);
    towerShape.setFillColor(sf::Color::Blue);
    towerShape.setOrigin({12.f, 12.f});
    for (const auto& tower : game.m_towers) {
        towerShape.setPosition(tower.pos);
        window.draw(towerShape);
    }

    // Draw projectiles
    game.m_projectilePool.DrawAll(window);

    // Draw gameplay status text (including map name)
    string statusStr = "Carte: " + game.m_mapName + "  |  PV: " + to_string(game.m_baseHp) + "  |  Or: " + to_string(game.m_gold) + "  |  [Espace] Nouvelle Vague  |  [Echap] Menu";
    sf::Text statusText(m_font, statusStr, 20);
    statusText.setFillColor(sf::Color::White);
    
    // Add a dark semi-transparent rectangle background for status text readability
    sf::RectangleShape hudBg(sf::Vector2f(1200.f, 50.f));
    hudBg.setFillColor(sf::Color(0, 0, 0, 180));
    hudBg.setPosition(sf::Vector2f(0.f, 0.f));
    window.draw(hudBg);

    statusText.setPosition(sf::Vector2f(20.f, 12.f));
    window.draw(statusText);
}
