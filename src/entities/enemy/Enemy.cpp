#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f startPos, float speed, int hp)
    : m_position(startPos)
    , m_speed(speed)
    , m_hp(hp)
{
}

void Enemy::update(const sf::Vector2f& playerPos, float deltaTime)
{
    sf::Vector2f direction = playerPos - m_position;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.001f)
    {
        direction /= length;
        m_position += direction * m_speed * deltaTime;
    }
}

sf::Vector2f Enemy::getPosition() const
{
    return m_position;
}

sf::Vector2f Enemy::getCenter() const
{
    // The origin is at the center
    return m_position;
}

bool Enemy::isDead() const
{
    return m_hp <= 0;
}

void Enemy::takeDamage(int amount)
{
    m_hp -= amount;
}
