#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.hpp"



// menu state
enum class MenuState {
    MainMenu,
    RulesMenu,
    Playing,
    Exit
};

class Menu {
private:
    MenuState m_state;
    sf::Font m_font;
    sf::Font m_boldFont;
    
    // text
    sf::Text m_title;
    sf::Text m_titleShadow;
    sf::Text m_rulesText;

    // buttons
    std::unique_ptr<Button> m_playBtn;
    std::unique_ptr<Button> m_rulesBtn;
    std::unique_ptr<Button> m_exitBtn;
    std::unique_ptr<Button> m_backBtn;

    // place
    void positionElements(sf::Vector2f windowSize);

public:
    Menu(sf::Vector2f windowSize);

    // methods
    void handleEvents(sf::RenderWindow& window);
    void update(sf::Vector2f mousePos, float deltaTime, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);

    // getters/setters
    MenuState getState() const { return m_state; }
    void setState(MenuState state) { m_state = state; }
};

#endif
