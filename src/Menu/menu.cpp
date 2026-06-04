#include "../Header/Menu.hpp"
#include "../SoundManager/SoundManager.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Helper function to load a texture and normalize all non-transparent pixels to solid white
static void loadAndNormalizeTexture(sf::Texture& texture, const std::string& filepath) {
    sf::Image img;
    if (img.loadFromFile(filepath)) {
        sf::Vector2u size = img.getSize();
        for (unsigned int y = 0; y < size.y; ++y) {
            for (unsigned int x = 0; x < size.x; ++x) {
                sf::Color color = img.getPixel({x, y});
                if (color.a > 0) {
                    // Repaint to solid white while preserving smooth anti-aliased alpha borders
                    img.setPixel({x, y}, sf::Color(255, 255, 255, color.a));
                }
            }
        }
        texture.loadFromImage(img);
    } else {
        std::cerr << "Warning: Could not load icon image file: " << filepath << std::endl;
    }
}

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

    // Load and normalize sound icons (filenames: off = speaker playing waves, on = speaker with X)
    loadAndNormalizeTexture(m_soundOnTex, "data/icons/icon_speak_off.png");
    loadAndNormalizeTexture(m_soundOffTex, "data/icons/icon_speak_on.png");

    // Instantiate buttons with dummy configurations initially
    m_playBtn = std::make_unique<Button>(m_font, "Jouer", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_rulesBtn = std::make_unique<Button>(m_font, "Regles", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_exitBtn = std::make_unique<Button>(m_font, "Quitter", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_backBtn = std::make_unique<Button>(m_font, "Retour", sf::Vector2f(0.f, 0.f), sf::Vector2f(200.f, 50.f));
    m_soundBtn = std::make_unique<Button>(m_font, "", sf::Vector2f(0.f, 0.f), sf::Vector2f(44.f, 44.f));

    // Bind texture to the sound toggle button
    m_soundBtn->setIcon(m_soundOnTex);

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

    // Determine scaled dimensions for standard text buttons
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

    // Place sound button in the top right corner
    sf::Vector2f soundBtnSize(44.f * scale, 44.f * scale);
    m_soundBtn->setSize(soundBtnSize, 0);
    m_soundBtn->setPosition(sf::Vector2f(windowSize.x - soundBtnSize.x - 20.f * scale, 20.f * scale));
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

                // Sound toggle button click check (available globally on all menu screens)
                if (m_soundBtn->isClicked(mappedMousePos)) {
                    SoundManager::getInstance().toggleMute();
                    if (SoundManager::getInstance().isMuted()) {
                        m_soundBtn->setIcon(m_soundOffTex);
                    } else {
                        m_soundBtn->setIcon(m_soundOnTex);
                    }
                }

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
    // Recycles finished audio channels
    SoundManager::getInstance().update();

    // Update global buttons
    m_soundBtn->update(mousePos, deltaTime);

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

    // Draw sound toggle button
    m_soundBtn->draw(window);

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
