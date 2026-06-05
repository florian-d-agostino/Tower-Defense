#include "../Header/Menu.hpp"
#include <cstdlib>
#include <ctime>

Menu::Menu(sf::Vector2f windowSize)
    : m_state(MenuState::MainMenu),
      m_font("data/fonts/segoeui.ttf"),
      m_boldFont("data/fonts/segoeuib.ttf"),
      m_title(m_boldFont, "TOWER DEFENSE", 50),
      m_titleShadow(m_boldFont, "TOWER DEFENSE", 50),
      m_rulesText(m_font, "", 20)
{
    // Configure visual appearance of titles and rules text
    m_title.setFillColor(sf::Color(0, 255, 200));
    m_titleShadow.setFillColor(sf::Color(128, 0, 128, 100));

    m_rulesText.setFillColor(sf::Color(220, 220, 240));
    m_rulesText.setString(
        "Regles du jeu :\n\n"
        "1. Placez des tours pour defendre le chemin.\n"
        "2. Tuez les ennemis pour obtenir de l'or.\n"
        "3. Ne laissez pas les ennemis atteindre votre base.\n"
        "4. Survivez a toutes les vagues pour gagner !"
    );

    // Instantiate buttons with dummy configurations initially
    m_playBtn = std::make_unique<Button>(m_font, "Jouer", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_rulesBtn = std::make_unique<Button>(m_font, "Regles", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_exitBtn = std::make_unique<Button>(m_font, "Quitter", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_backBtn = std::make_unique<Button>(m_font, "Retour", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));

    // Place and size all menu items
    positionElements(windowSize);
}

void Menu::positionElements(sf::Vector2f windowSize) {
    // Determine scaling ratio relative to base height (800)
    float scale = windowSize.y / 800.f;
    if (scale < 0.5f) scale = 0.5f;

    // Apply scaling factor to font character sizes
    m_title.setCharacterSize(static_cast<unsigned int>(50.f * scale));
    m_titleShadow.setCharacterSize(static_cast<unsigned int>(50.f * scale));
    m_rulesText.setCharacterSize(static_cast<unsigned int>(20.f * scale));

    // Center and place Title and its shadow
    sf::FloatRect titleBounds = m_title.getLocalBounds();
    m_title.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f, titleBounds.position.y + titleBounds.size.y / 2.f});
    m_title.setPosition({windowSize.x / 2.f, windowSize.y * 0.18f});

    m_titleShadow.setOrigin(m_title.getOrigin());
    m_titleShadow.setPosition({windowSize.x / 2.f + 4.f * scale, windowSize.y * 0.18f + 4.f * scale});

    // Center and place Rules text
    sf::FloatRect rulesBounds = m_rulesText.getLocalBounds();
    m_rulesText.setOrigin({rulesBounds.position.x + rulesBounds.size.x / 2.f, rulesBounds.position.y + rulesBounds.size.y / 2.f});
    m_rulesText.setPosition({windowSize.x / 2.f, windowSize.y * 0.42f});

    // Determine scaled dimensions for buttons
    sf::Vector2f btnSize(200.f * scale, 50.f * scale);
    unsigned int btnCharSize = static_cast<unsigned int>(22.f * scale);

    // Apply sizes and positions to button instances
    m_playBtn->setSize(btnSize, btnCharSize);
    m_rulesBtn->setSize(btnSize, btnCharSize);
    m_exitBtn->setSize(btnSize, btnCharSize);
    m_backBtn->setSize(btnSize, btnCharSize);

    m_playBtn->setPosition(sf::Vector2f(windowSize.x / 2.f - btnSize.x / 2.f, windowSize.y * 0.38f));
    m_rulesBtn->setPosition(sf::Vector2f(windowSize.x / 2.f - btnSize.x / 2.f, windowSize.y * 0.48f));
    m_exitBtn->setPosition(sf::Vector2f(windowSize.x / 2.f - btnSize.x / 2.f, windowSize.y * 0.58f));
    m_backBtn->setPosition(sf::Vector2f(windowSize.x / 2.f - btnSize.x / 2.f, windowSize.y * 0.7f));
}

void Menu::handleEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        // Handle window close
        if (event->is<sf::Event::Closed>()) {
            m_state = MenuState::Exit;
            window.close();
        }

        // Adjust view boundaries and component layout on window resize
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
            window.setView(sf::View(visibleArea));
            positionElements(sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)));
        }

        // Process mouse button clicks using mapped view coordinates
        if (const auto* press = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (press->button == sf::Mouse::Button::Left) {
                sf::Vector2f mappedMousePos = window.mapPixelToCoords(press->position);
                if (m_state == MenuState::MainMenu) {
                    if (m_playBtn->isClicked(mappedMousePos)) {
                        m_state = MenuState::Playing;
                    } else if (m_rulesBtn->isClicked(mappedMousePos)) {
                        m_state = MenuState::RulesMenu;
                    } else if (m_exitBtn->isClicked(mappedMousePos)) {
                        m_state = MenuState::Exit;
                    }
                } else if (m_state == MenuState::RulesMenu) {
                    if (m_backBtn->isClicked(mappedMousePos)) {
                        m_state = MenuState::MainMenu;
                    }
                }
            }
        }
    }
}

void Menu::update(sf::Vector2f mousePos, float deltaTime, sf::Vector2f windowSize) {
    // Update button states depending on current menu state
    if (m_state == MenuState::MainMenu) {
        m_playBtn->update(mousePos, deltaTime);
        m_rulesBtn->update(mousePos, deltaTime);
        m_exitBtn->update(mousePos, deltaTime);
    } else if (m_state == MenuState::RulesMenu) {
        m_backBtn->update(mousePos, deltaTime);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    // Clear screen to deep blue color
    window.clear(sf::Color(10, 10, 25));

    // Render active UI elements depending on state
    if (m_state == MenuState::MainMenu) {
        window.draw(m_titleShadow);
        window.draw(m_title);
        m_playBtn->draw(window);
        m_rulesBtn->draw(window);
        m_exitBtn->draw(window);
    } else if (m_state == MenuState::RulesMenu) {
        window.draw(m_rulesText);
        m_backBtn->draw(window);
    }
}
