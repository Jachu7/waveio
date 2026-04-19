#include "Player.hpp"
#include "core/Constants.hpp"
#include "core/AssetManager.hpp"
#include <algorithm>
#include <cmath>

Player::Player()
    : m_sprite(AssetManager::getInstance().getTexture("player"))
    , m_speed(PLAYER_SPEED)
    , m_hp(PLAYER_MAX_HP)
    , m_isMoving(false)
    , m_facingRight(true)
    , m_animationTime(0.f)
    , m_currentFrame(0)
{
    m_sprite.setTextureRect(sf::IntRect({0, 0}, {24, 24}));
    m_sprite.setScale({PLAYER_SCALE, PLAYER_SCALE});
    m_sprite.setOrigin({12.f, 12.f});
    m_sprite.setPosition({PLAYER_START_X, PLAYER_START_Y});
}

void Player::handleInput(float deltaTime)
{
    sf::Vector2f movement{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    const float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length > 0.001f) // unikamy /0
    {
        movement /= length;
        m_sprite.move(movement * m_speed * deltaTime);

        m_isMoving = true;
        if (movement.x > 0.f) m_facingRight = true;
        else if (movement.x < 0.f) m_facingRight = false;
    }
    else
    {
        m_isMoving = false;
    }
}

void Player::updateAnimation(float deltaTime)
{
    const float frameDuration = 0.15f;
    m_animationTime += deltaTime;

    if (m_animationTime >= frameDuration)
    {
        m_animationTime = 0.f;
        m_currentFrame++;
    }

    int row = 0;
    int maxFrames = 2; // Idle ma 2 klatki (rzad 1)

    if (m_isMoving)
    {
        row = 1;       // Poruszanie to rzad 2
        maxFrames = 4; // Poruszanie ma 4 klatki
    }

    if (m_currentFrame >= maxFrames)
    {
        m_currentFrame = 0;
    }

    m_sprite.setTextureRect(sf::IntRect({m_currentFrame * 24, row * 24}, {24, 24}));

    float scaleX = PLAYER_SCALE * (m_facingRight ? 1.f : -1.f);
    m_sprite.setScale({scaleX, PLAYER_SCALE});
}

void Player::update(float deltaTime)
{
    updateAnimation(deltaTime);
    clampToMap();
}

void Player::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

sf::Vector2f Player::getCenter() const
{
    return m_sprite.getPosition();
}

int Player::getHp() const
{
    return m_hp;
}

float Player::getSpeed() const
{
    return m_speed;
}

void Player::takeDamage(int amount)
{
    m_hp = std::max(0, m_hp - amount);
}

void Player::heal(int amount)
{
    m_hp = std::min(PLAYER_MAX_HP, m_hp + amount);
}

void Player::clampToMap()
{
    sf::Vector2f pos = m_sprite.getPosition();

    const float halfX = 5.f * PLAYER_SCALE;
    const float halfY_top = 4.f * PLAYER_SCALE;
    const float halfY_bot = 10.f * PLAYER_SCALE;

    pos.x = std::clamp(pos.x, halfX, MAP_WIDTH - halfX);
    pos.y = std::clamp(pos.y, halfY_top, MAP_HEIGHT - halfY_bot);

    m_sprite.setPosition(pos);
}
