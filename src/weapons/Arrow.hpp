#pragma once

#include <SFML/Graphics.hpp>

class Arrow
{
public:
    Arrow(sf::Vector2f startPos, sf::Vector2f targetPos);

    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    bool isOutOfBounds(float mapWidth, float mapHeight) const;
    bool isActive() const;
    void destroy();

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_speed;
    bool m_active;
};
