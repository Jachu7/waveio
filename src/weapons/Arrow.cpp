#include "Arrow.hpp"
#include "../core/AssetManager.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Arrow::Arrow(sf::Vector2f startPos, sf::Vector2f targetPos)
    : m_sprite(AssetManager::getInstance().getTexture("arrow"))
    , m_speed(300.f)
    , m_active(true)
{
    m_sprite.setOrigin({m_sprite.getLocalBounds().size.x / 2.f, m_sprite.getLocalBounds().size.y / 2.f});
    m_sprite.setPosition(startPos);
    m_sprite.setScale({0.50f, 0.50f});

    sf::Vector2f direction = targetPos - startPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (length > 0.001f)
    {
        direction /= length;
    }
    else
    {
        direction = {1.f, 0.f}; // default direction if target is exactly on start
    }
    
    m_velocity = direction * m_speed;

    float angleDegrees = std::atan2(direction.y, direction.x) * 180.f / M_PI;
    m_sprite.setRotation(sf::degrees(angleDegrees)); // SFML 3 expects sf::degrees or sf::radians
}

void Arrow::update(float deltaTime)
{
    if (m_active)
    {
        m_sprite.move(m_velocity * deltaTime);
    }
}

void Arrow::render(sf::RenderWindow& window) const
{
    if (m_active)
    {
        // Rysowanie prawdziwej grafiki strzały
        window.draw(m_sprite);
        
        // Debug: Rysowanie malutkiego kropko-hitboxa (grota)
        sf::FloatRect bounds = getBounds();
        sf::RectangleShape tipBox(bounds.size);
        tipBox.setPosition(bounds.position);
        tipBox.setFillColor(sf::Color::Red);
        window.draw(tipBox);
    }
}

sf::FloatRect Arrow::getBounds() const
{
    sf::Vector2f dir;
    if (m_speed > 0.f)
        dir = m_velocity / m_speed;
    else
        dir = {1.f, 0.f};

    // Promień (połowa długości strzały) ze zmniejszoną skalą
    float arrowLength = std::max(m_sprite.getLocalBounds().size.x, m_sprite.getLocalBounds().size.y) * 0.33f;
    // Odsunięcie od środka do ostrza (mnożymy przez 0.8, żeby trochę zignorować ewentualne puste piksele na brzegach grafiki)
    float distanceToTip = (arrowLength / 2.f) * 0.8f;
    
    sf::Vector2f pos = m_sprite.getPosition();
    sf::Vector2f tipPos = pos + dir * distanceToTip;
    
    // Zwróć mały prostokącik 6x6 pikseli znajdujący się na końcu lotu (grocie)
    return sf::FloatRect({tipPos.x - 3.f, tipPos.y - 3.f}, {6.f, 6.f});
}

bool Arrow::isOutOfBounds(float mapWidth, float mapHeight) const
{
    sf::Vector2f pos = m_sprite.getPosition();
    return (pos.x < 0 || pos.x > mapWidth || pos.y < 0 || pos.y > mapHeight);
}

bool Arrow::isActive() const
{
    return m_active;
}

void Arrow::destroy()
{
    m_active = false;
}
