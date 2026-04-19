#pragma once

#include <SFML/Graphics.hpp>

class MapBackground
{
public:
    MapBackground();

    void render(sf::RenderWindow& window) const;

private:
    sf::Sprite m_sprite;
};
