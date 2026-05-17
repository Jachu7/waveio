#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(sf::Vector2f startPos, float speed, int hp);
    virtual ~Enemy() = default;

    virtual void update(const sf::Vector2f& playerPos, float deltaTime);
    virtual void render(sf::RenderWindow& window) const = 0;

    virtual sf::FloatRect getBounds() const = 0;
    
    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;

    bool isDead() const;
    void takeDamage(int amount);

protected:
    sf::Vector2f m_position;
    float m_speed;
    int m_hp;
};
