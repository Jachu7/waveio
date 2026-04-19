#include "Game.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"

#include <iostream>
#include <stdexcept>

Game::Game()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Waveio", sf::State::Fullscreen)
    , m_uiView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)}))
    , m_camera({VIEW_WIDTH, VIEW_HEIGHT}, {MAP_WIDTH, MAP_HEIGHT})
    , m_assetsLoaded(initAssets())
{
    m_window.setFramerateLimit(FRAMERATE_LIMIT);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        const float deltaTime = m_clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
                m_window.close();
        }
    }
}

void Game::update(float deltaTime)
{
    m_player.handleInput(deltaTime);
    m_player.update(deltaTime);

    m_camera.follow(m_player.getCenter());
}

void Game::render()
{
    m_window.clear();

    m_window.setView(m_camera.getView());
    m_mapBackground.render(m_window);
    m_player.render(m_window);

    m_window.setView(m_uiView);
    // TODO: rysuj elementy HUD tutaj

    m_window.display();
}

bool Game::initAssets()
{
    AssetManager::getInstance().loadTexture("mapa", Paths::TEXTURE_MAP);
    AssetManager::getInstance().loadTexture("player", Paths::TEXTURE_PLAYER);
    return true;
}
