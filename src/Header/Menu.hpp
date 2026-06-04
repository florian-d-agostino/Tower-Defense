#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.hpp"

// Represents the screen/views of the game menu
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
    
    // UI Text components
    sf::Text m_title;
    sf::Text m_titleShadow;
    sf::Text m_rulesText;

    // Interactive buttons
    std::unique_ptr<Button> m_playBtn;
    std::unique_ptr<Button> m_rulesBtn;
    std::unique_ptr<Button> m_exitBtn;
    std::unique_ptr<Button> m_backBtn;
    std::unique_ptr<Button> m_soundBtn;

    sf::Texture m_soundOnTex;
    sf::Texture m_soundOffTex;

    // Repositions and scales all components dynamically
    void positionElements(sf::Vector2f windowSize);

public:
    Menu(sf::Vector2f windowSize);

    // Event handling, layout update, rendering
    void handleEvents(sf::RenderWindow& window);
    void update(sf::Vector2f mousePos, float deltaTime, sf::Vector2f windowSize);
    void draw(sf::RenderWindow& window);

    // State getters and setters
    MenuState getState() const { return m_state; }
    void setState(MenuState state) { m_state = state; }
};

#endif
