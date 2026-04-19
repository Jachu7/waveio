#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "MapBackground.hpp"
#include "entities/Player.hpp"

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

    sf::Clock m_clock;
};
