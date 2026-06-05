#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <SFML/Graphics.hpp>

class GameManager; // Forward declaration

class GameRenderer {
private:
    sf::Font m_font;

public:
    GameRenderer();

    // Renders the entire game view
    void draw(sf::RenderWindow& window, GameManager& game);
};

#endif // GAME_RENDERER_HPP
