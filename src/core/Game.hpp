#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "MapBackground.hpp"
#include "entities/Player.hpp"
#include "ui/InGameInterface.hpp"
#include "entities/Enemy.hpp"
#include "weapons/Arrow.hpp"
#include "WaveLoop.hpp"
#include <memory>
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    static bool initAssets();

    sf::RenderWindow m_window;
    sf::View m_uiView;
    Camera m_camera;

    bool m_assetsLoaded;
    MapBackground m_mapBackground;
    Player m_player;
    std::unique_ptr<InGameInterface> m_inGameInterface;

    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Arrow>> m_arrows;
    float m_shootTimer;

    sf::Clock m_clock;

    WaveLoop m_waveLoop;
    bool m_isWavePaused;
};