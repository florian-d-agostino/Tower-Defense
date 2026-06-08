#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <SFML/Graphics.hpp>

class GameManager; 

class GameRenderer {
private:
    sf::Font m_font;

public:
    GameRenderer();



    // draw
    void draw(sf::RenderWindow& window, GameManager& game);
};

#endif
