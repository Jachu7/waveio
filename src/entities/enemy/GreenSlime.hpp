#pragma once

#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class GreenSlime : public Enemy
{
public:
    GreenSlime(sf::Vector2f startPos);

    void update(const sf::Vector2f& playerPos, float deltaTime) override;
    void render(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

private:
    void updateAnimation(float deltaTime);

    sf::Sprite m_sprite;
    std::vector<const sf::Texture*> m_walkTextures;
    
    float m_animationTime;
    int m_currentFrame;
    bool m_facingRight;
};
