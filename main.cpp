#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Header/Menu.hpp"
#include "src/Header/GameManager.hpp"
#include "src/Header/GameRenderer.hpp"

int main() {
    // window setup
    sf::Vector2f windowSize(1200.f, 800.f);
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Tower Defense");
    window.setFramerateLimit(60);

    // init menu and game
    Menu menu(windowSize);
    GameManager gameManager;
    GameRenderer gameRenderer;
    sf::Clock clock;

    // game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // mouse pos
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePosI);

        // input
        if (menu.getState() == MenuState::Playing) {
            gameManager.handleEvents(window, menu);
        } else {
            menu.handleEvents(window);
        }

        // quit
        if (menu.getState() == MenuState::Exit) {
            window.close();
            break;
        }

        // update
        if (menu.getState() == MenuState::Playing) {
            gameManager.update(deltaTime);
        } else {
            // window size
            sf::Vector2f currentSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
            menu.update(mousePos, deltaTime, currentSize);
        }

        // draw
        window.clear();
        if (menu.getState() == MenuState::Playing) {
            gameRenderer.draw(window, gameManager);
        } else {
            menu.draw(window);
        }
        window.display();
    }

    std::cout << "App close." << std::endl;
    return 0;
}
