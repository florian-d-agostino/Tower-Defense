#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

// Represents an interactive, styled UI button
class Button {
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    bool m_isHovered;
    float m_hoverProgress; // Tracks hover transition progress (0.0 to 1.0)

    // Style colors for normal and hover states
    sf::Color m_normalFill;
    sf::Color m_hoverFill;
    sf::Color m_normalOutline;
    sf::Color m_hoverOutline;
    sf::Color m_normalText;
    sf::Color m_hoverText;

public:
    Button(const sf::Font& font, const std::string& label, sf::Vector2f position, sf::Vector2f size);

    // Dynamic layout/scaling management
    void setSize(sf::Vector2f size, unsigned int charSize);
    void setPosition(sf::Vector2f position);
    
    // Logic, render and interaction
    void update(sf::Vector2f mousePos, float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isClicked(sf::Vector2f mousePos) const;
};

#endif
