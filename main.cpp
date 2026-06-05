#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Header/Menu.hpp"
#include "src/Header/GameManager.hpp"
#include "src/Header/GameRenderer.hpp"

int main() {
    // Initial window dimensions and setup
    sf::Vector2f windowSize(1200.f, 800.f);
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Tower Defense");
    window.setFramerateLimit(60);

    // Initialize menu, game manager, game renderer, and clock for frame time calculation
    Menu menu(windowSize);
    GameManager gameManager;
    GameRenderer gameRenderer;
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Map mouse screen coordinates to virtual view coordinates
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI);

        // Process inputs and window events based on state
        if (menu.getState() == MenuState::Playing) {
            gameManager.handleEvents(window, menu);
        } else {
            menu.handleEvents(window);
        }

        // Exit game loop if Exit state is active
        if (menu.getState() == MenuState::Exit) {
            window.close();
            break;
        }

        // Update positions based on state
        if (menu.getState() == MenuState::Playing) {
            gameManager.update(deltaTime);
        } else {
            // Get actual window size dynamically to update menu positions
            sf::Vector2f currentSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
            menu.update(mousePos, deltaTime, currentSize);
        }

        // Render everything based on state
        window.clear();
        if (menu.getState() == MenuState::Playing) {
            gameRenderer.draw(window, gameManager);
        } else {
            menu.draw(window);
        }
        window.display();
    }

    std::cout << "Fermeture du jeu..." << std::endl;
    return 0;
}
