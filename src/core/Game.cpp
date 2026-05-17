#include "Game.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"
#include "entities/enemies/GreenSlime.hpp"
#include "WaveLoop.hpp" 

#include <iostream>
#include <stdexcept>
#include <random>

Game::Game()
    : m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Waveio", sf::State::Fullscreen)
    , m_uiView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)}))
    , m_camera({VIEW_WIDTH, VIEW_HEIGHT}, {MAP_WIDTH, MAP_HEIGHT})
    , m_assetsLoaded(initAssets())
    , m_shootTimer(0.f)
    , m_isWavePaused(true)
{
    m_inGameInterface = std::make_unique<InGameInterface>();
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
            else if (key->code == sf::Keyboard::Key::Space && m_isWavePaused)
            {
                m_isWavePaused = false;
            }
        }
    }
}

void Game::update(float deltaTime)
{
    if (m_inGameInterface)//Update in-game interface so when game is paused we can still see player stats
        m_inGameInterface->update(m_player, m_waveLoop.getWaveNumber());

    if (m_isWavePaused)//Pause game while the screen after wave is on
        return;

    m_player.handleInput(deltaTime);
    m_player.update(deltaTime);

    // Enemy Spawning Logika
    m_waveLoop.WaveSystem(deltaTime, m_enemies);

    // Shooting logika
    m_shootTimer += deltaTime;
    if (m_shootTimer >= 1.0f && !m_enemies.empty())
    {
        // znajdz najblizszego wroga
        Enemy* nearestEnemy = nullptr;
        float minDistanceSq = std::numeric_limits<float>::max();
        sf::Vector2f playerPos = m_player.getCenter();

        for (const auto& enemy : m_enemies)
        {
            sf::Vector2f diff = enemy->getCenter() - playerPos;
            float distSq = diff.x * diff.x + diff.y * diff.y;
            if (distSq < minDistanceSq)
            {
                minDistanceSq = distSq;
                nearestEnemy = enemy.get();
            }
        }

        if (nearestEnemy)
        {
            m_arrows.push_back(std::make_unique<Arrow>(playerPos, nearestEnemy->getCenter()));
        }
        m_shootTimer = 0.f;
    }

    // Aktualizacja wrogow
    for (auto& enemy : m_enemies)
    {
        enemy->update(m_player.getCenter(), deltaTime);
    }

    // Aktualizacja strzal i kolizje
    for (auto& arrow : m_arrows)
    {
        arrow->update(deltaTime);

        // Jesli strzala poza mapa to usun (niszczenie)
        if (arrow->isOutOfBounds(MAP_WIDTH, MAP_HEIGHT)) {
            arrow->destroy();
        }

        if (!arrow->isActive()) continue;

        // Kolizje z przeciwnikami
        for (auto& enemy : m_enemies)
        {
            if (!enemy->isDead() && arrow->getBounds().findIntersection(enemy->getBounds()))
            {
                // Trafienie
                enemy->takeDamage(1); 
                arrow->destroy();
                
                if (enemy->isDead()) {
                    m_player.addMoney(1);
                }
                break; // Jedna strzala trafia jednego wroga
            }
        }
    }

    // Usuwanie martwych obiektow
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
        [](const std::unique_ptr<Enemy>& e) { return e->isDead(); }), m_enemies.end());

    m_arrows.erase(std::remove_if(m_arrows.begin(), m_arrows.end(),
        [](const std::unique_ptr<Arrow>& a) { return !a->isActive(); }), m_arrows.end());

    m_camera.follow(m_player.getCenter());
    
    if (m_waveLoop.isWaveComplete())//Initializing next wave 
    {
        m_isWavePaused = true;
        m_waveLoop.startNextWave();
    }
}

void Game::render()
{
    m_window.clear();

    m_window.setView(m_camera.getView());
    m_mapBackground.render(m_window);
    
    for (const auto& enemy : m_enemies)
        enemy->render(m_window);
        
    m_player.render(m_window);
    
    for (const auto& arrow : m_arrows)
        arrow->render(m_window);

    m_window.setView(m_uiView);
    if (m_inGameInterface)
        m_inGameInterface->render(m_window);

    if (m_isWavePaused)//Wave pausee screen
    {
        sf::RectangleShape popup(sf::Vector2f(600.f, 400.f));
        popup.setFillColor(sf::Color(50, 50, 50, 200));
        popup.setPosition({(WINDOW_WIDTH - 600.f) / 2.f, (WINDOW_HEIGHT - 400.f) / 2.f});
        popup.setOutlineThickness(5.f);
        popup.setOutlineColor(sf::Color::White);
        m_window.draw(popup);

        sf::Text title(AssetManager::getInstance().getFont("main_font"));
        title.setString("Wave " + std::to_string(m_waveLoop.getWaveNumber()));
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::Yellow);
        sf::FloatRect textRect = title.getLocalBounds();
        title.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
        title.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 50.f});
        m_window.draw(title);

        sf::Text prompt(AssetManager::getInstance().getFont("main_font"));
        prompt.setString("Press SPACE to start");
        prompt.setCharacterSize(30);
        prompt.setFillColor(sf::Color::White);
        sf::FloatRect promptRect = prompt.getLocalBounds();
        prompt.setOrigin({promptRect.position.x + promptRect.size.x / 2.0f, promptRect.position.y + promptRect.size.y / 2.0f});
        prompt.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50.f});
        m_window.draw(prompt);
    }

    m_window.display();
}

bool Game::initAssets()
{
    AssetManager::getInstance().loadTexture("mapa", Paths::TEXTURE_MAP);
    AssetManager::getInstance().loadTexture("player", Paths::TEXTURE_PLAYER);
    AssetManager::getInstance().loadTexture("coin", Paths::TEXTURE_COIN);
    AssetManager::getInstance().loadTexture("heart", Paths::TEXTURE_HEART);
    AssetManager::getInstance().loadTexture("arrow", Paths::TEXTURE_ARROW);
    AssetManager::getInstance().loadTexture("slime_walk_0", Paths::TEXTURE_SLIME_WALK_0);
    AssetManager::getInstance().loadTexture("slime_walk_1", Paths::TEXTURE_SLIME_WALK_1);
    AssetManager::getInstance().loadTexture("slime_walk_2", Paths::TEXTURE_SLIME_WALK_2);
    AssetManager::getInstance().loadTexture("slime_walk_3", Paths::TEXTURE_SLIME_WALK_3);
    AssetManager::getInstance().loadTexture("slime_walk_4", Paths::TEXTURE_SLIME_WALK_4);
    AssetManager::getInstance().loadTexture("slime_walk_5", Paths::TEXTURE_SLIME_WALK_5);
    AssetManager::getInstance().loadFont("main_font", Paths::FONT_MAIN);
    return true;
}
