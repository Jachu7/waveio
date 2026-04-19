#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();

    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;    
    int getHp() const;
    float getSpeed() const;

    void takeDamage(int amount);
    void heal(int amount);

private:
    void clampToMap();
    void updateAnimation(float deltaTime);

    sf::Sprite m_sprite;

    float m_speed;
    int m_hp;

    bool m_isMoving;
    bool m_facingRight;
    float m_animationTime;
    int m_currentFrame;
};
