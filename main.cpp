#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Header/Menu.hpp"

int main() {
    // Initial window dimensions and setup
    sf::Vector2f windowSize(1200.f, 800.f);
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Tower Defense");
    window.setFramerateLimit(60);

    // Initialize menu and clock for frame time calculation
    Menu menu(windowSize);
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Map mouse screen coordinates to virtual view coordinates
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI);

        // Process inputs and window events
        menu.handleEvents(window);

        // Exit game loop if Exit state is active
        if (menu.getState() == MenuState::Exit) {
            window.close();
            break;
        }

        // Get actual window size dynamically to update positions
        sf::Vector2f currentSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
        menu.update(mousePos, deltaTime, currentSize);

        // Render everything
        window.clear();
        menu.draw(window);
        window.display();
    }

    std::cout << "Fermeture du jeu..." << std::endl;
    return 0;
}
