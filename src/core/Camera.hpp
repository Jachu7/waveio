#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(sf::Vector2f viewSize, sf::Vector2f mapSize);

    void follow(sf::Vector2f targetPosition);
    const sf::View& getView() const;

private:
    sf::View m_view;
    sf::Vector2f m_mapSize;

    sf::Vector2f clampCenter(sf::Vector2f center) const;
};
