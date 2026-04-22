#include "GreenSlime.hpp"
#include "../../core/AssetManager.hpp"
#include <cmath>

GreenSlime::GreenSlime(sf::Vector2f startPos)
    : Enemy(startPos, 50.f, 1) // default speed 50, hp 1
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

    // Force perfect 24x24 px bounds according to user requests
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setScale({24.f / bounds.size.x, 24.f / bounds.size.y});
    
    // Set origin to center
    m_sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    m_sprite.setPosition(m_position);
}

void GreenSlime::update(const sf::Vector2f& playerPos, float deltaTime)
{
    // Czysta matematyka poruszania
    sf::Vector2f oldPos = m_position;
    Enemy::update(playerPos, deltaTime);
    
    sf::Vector2f diff = m_position - oldPos;
    if (diff.x > 0.001f) m_facingRight = true;
    else if (diff.x < -0.001f) m_facingRight = false;
    
    m_sprite.setPosition(m_position);
    updateAnimation(deltaTime);
}

void GreenSlime::updateAnimation(float deltaTime)
{
    float frameDuration = 0.15f;
    m_animationTime += deltaTime;
    
    if (m_animationTime >= frameDuration)
    {
        m_animationTime = 0.f;
        m_currentFrame = (m_currentFrame + 1) % m_walkTextures.size();
        m_sprite.setTexture(*m_walkTextures[m_currentFrame]);
    }
    
    // Flip depending on direction
    float scaleX = std::abs(m_sprite.getScale().x);
    if (!m_facingRight) scaleX = -scaleX;
        
    m_sprite.setScale({scaleX, std::abs(m_sprite.getScale().y)});
}

void GreenSlime::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
    
    // Rysowanie testowego AABB na żądanie użytkownika (czerwony)
    sf::FloatRect bounds = getBounds();
    sf::RectangleShape debugBox(bounds.size);
    debugBox.setPosition(bounds.position);
    debugBox.setFillColor(sf::Color(255, 0, 0, 100)); // Półprzezroczysty zeby grafikę było widać
    window.draw(debugBox);
}

sf::FloatRect GreenSlime::getBounds() const
{
    return m_sprite.getGlobalBounds();
}
