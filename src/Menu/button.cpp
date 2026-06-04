#include <cstdint>
#include "../Header/Button.hpp"

// Linearly interpolates two colors for smooth transitions
static sf::Color lerpColor(sf::Color normal, sf::Color hover, float t) {
    return sf::Color(
        static_cast<std::uint8_t>(normal.r + (hover.r - normal.r) * t),
        static_cast<std::uint8_t>(normal.g + (hover.g - normal.g) * t),
        static_cast<std::uint8_t>(normal.b + (hover.b - normal.b) * t),
        static_cast<std::uint8_t>(normal.a + (hover.a - normal.a) * t)
    );
}

Button::Button(const sf::Font& font, const std::string& label, sf::Vector2f position, sf::Vector2f size)
    : m_text(font, label), m_isHovered(false), m_hoverProgress(0.0f) 
{
    // Define color presets
    m_normalFill = sf::Color(19, 19, 38, 100);
    m_hoverFill = sf::Color(64, 224, 208, 40);
    m_normalOutline = sf::Color(100, 100, 120);
    m_hoverOutline = sf::Color(64, 224, 208);
    m_normalText = sf::Color(200, 200, 200);
    m_hoverText = sf::Color(255, 255, 255);

    // Apply rectangle properties
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(m_normalFill);
    m_shape.setOutlineColor(m_normalOutline);
    m_shape.setOutlineThickness(2.0f);

    // Apply text properties
    m_text.setCharacterSize(22);
    m_text.setFillColor(m_normalText);

    // Center text in button
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f});
    m_text.setPosition({position.x + size.x / 2.f, position.y + size.y / 2.f});
}

void Button::setSize(sf::Vector2f size, unsigned int charSize) {
    m_shape.setSize(size);
    m_text.setCharacterSize(charSize);
    
    // Recenter text inside resized button shape
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f});
    m_text.setPosition({m_shape.getPosition().x + size.x / 2.f, m_shape.getPosition().y + size.y / 2.f});
}

void Button::setPosition(sf::Vector2f position) {
    m_shape.setPosition(position);
    
    // Recenter text inside repositioned button shape
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f});
    m_text.setPosition({position.x + m_shape.getSize().x / 2.f, position.y + m_shape.getSize().y / 2.f});
}

void Button::update(sf::Vector2f mousePos, float deltaTime) {
    // Check mouse containment
    m_isHovered = m_shape.getGlobalBounds().contains(mousePos);

    // Smooth color animation interpolation
    float target = m_isHovered ? 1.0f : 0.0f;
    m_hoverProgress += (target - m_hoverProgress) * deltaTime * 12.0f;
    if (m_hoverProgress < 0.0f) m_hoverProgress = 0.0f;
    if (m_hoverProgress > 1.0f) m_hoverProgress = 1.0f;

    // Apply color values based on interpolation
    m_shape.setFillColor(lerpColor(m_normalFill, m_hoverFill, m_hoverProgress));
    m_shape.setOutlineColor(lerpColor(m_normalOutline, m_hoverOutline, m_hoverProgress));
    m_text.setFillColor(lerpColor(m_normalText, m_hoverText, m_hoverProgress));
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    window.draw(m_text);
}

bool Button::isClicked(sf::Vector2f mousePos) const {
    return m_shape.getGlobalBounds().contains(mousePos);
}
