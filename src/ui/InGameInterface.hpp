#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Player.hpp"

class InGameInterface
{
public:
    InGameInterface();

    void update(const Player& player, int waveNumber);
    void render(sf::RenderWindow& window) const;

private:
    sf::Sprite m_coinIcon;
    sf::Sprite m_heartIcon;
    
    sf::Text m_moneyText;
    
    sf::RectangleShape m_healthBarBackground;
    sf::RectangleShape m_healthBarForeground;
    sf::Text m_healthText;
    sf::Text m_waveText;

    int m_maxHp;
};
