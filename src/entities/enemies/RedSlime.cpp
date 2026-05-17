#include "RedSlime.hpp"
#include "../../core/AssetManager.hpp"
#include <cmath>

RedSlime::RedSlime(sf::Vector2f startPos)
    : Enemy(startPos, 70.f, 2) // Faster speed, slightly more hp
    , m_sprite(AssetManager::getInstance().getTexture("slime_walk_0"))
    , m_animationTime(0.f)
    , m_currentFrame(0)
    , m_facingRight(true)
{
    // Load animation textures
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_0"));
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_1"));
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_2"));
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_3"));
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_4"));
    m_walkTextures.push_back(&AssetManager::getInstance().getTexture("slime_walk_5"));

    m_sprite.setTexture(*m_walkTextures[0]);
    m_sprite.setColor(sf::Color(255, 100, 100)); // Tint it red

    // Force perfect 24x24 px bounds according to user requests
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setScale({48.f / bounds.size.x, 48.f / bounds.size.y});
    
    // Set origin to center
    m_sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    m_sprite.setPosition(m_position);
}

void RedSlime::update(const sf::Vector2f& playerPos, float deltaTime)
{
    sf::Vector2f oldPos = m_position;
    Enemy::update(playerPos, deltaTime);
    
    sf::Vector2f diff = m_position - oldPos;
    if (diff.x > 0.001f) m_facingRight = true;
    else if (diff.x < -0.001f) m_facingRight = false;
    
    m_sprite.setPosition(m_position);
    updateAnimation(deltaTime);
}

void RedSlime::updateAnimation(float deltaTime)
{
    float frameDuration = 0.12f; // Faster animation
    m_animationTime += deltaTime;
    
    if (m_animationTime >= frameDuration)
    {
        m_animationTime = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_walkTextures.size();
        m_sprite.setTexture(*m_walkTextures[m_currentFrame]);
    }
    
    float scaleX = std::abs(m_sprite.getScale().x);
    if (!m_facingRight) scaleX = -scaleX;
        
    m_sprite.setScale({scaleX, std::abs(m_sprite.getScale().y)});
}

void RedSlime::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
    
    sf::FloatRect bounds = getBounds();
    sf::RectangleShape debugBox(bounds.size);
    debugBox.setPosition(bounds.position);
    debugBox.setFillColor(sf::Color(255, 0, 0, 100)); 
    window.draw(debugBox);
}

sf::FloatRect RedSlime::getBounds() const
{
    return m_sprite.getGlobalBounds();
}
