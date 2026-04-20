#include "InGameInterface.hpp"
#include "core/AssetManager.hpp"
#include "core/Constants.hpp"
#include <string>

InGameInterface::InGameInterface()
    : m_coinIcon(AssetManager::getInstance().getTexture("coin"))
    , m_heartIcon(AssetManager::getInstance().getTexture("heart"))
    , m_moneyText(AssetManager::getInstance().getFont("main_font"))
    , m_healthText(AssetManager::getInstance().getFont("main_font"))
    , m_maxHp(PLAYER_MAX_HP)
{
    // Money UI
    sf::Vector2u coinSize = m_coinIcon.getTexture().getSize();
    float coinScale = 80.f / coinSize.y; // Wysokość ikonki ~80px
    m_coinIcon.setScale({coinScale, coinScale});
    m_coinIcon.setPosition({20.f, 20.f});
    
    m_moneyText.setCharacterSize(60);
    m_moneyText.setFillColor(sf::Color::White);
    m_moneyText.setPosition({105.f, 16.f}); // Podniesiono w górę (czcionka była za nisko)

    // Health UI
    sf::Vector2u heartSize = m_heartIcon.getTexture().getSize();
    float heartScale = 80.f / heartSize.y; // Wysokość ikonki ~80px
    m_heartIcon.setScale({heartScale, heartScale});
    m_heartIcon.setPosition({20.f, 120.f}); // Pod ikoną coin, która zaczyna się w 20 i ma 80 wys, plus 20px paddingu

    // Pasek zdrowia zaczyna się od środka serca (X = 20 + 80/2 = 60)
    m_healthBarBackground.setSize({300.f, 35.f});
    m_healthBarBackground.setFillColor(sf::Color(100, 100, 100, 200));
    m_healthBarBackground.setPosition({60.f, 145.f}); // X=60 (środek serca), Y=145 (minimalnie obniżone z 142 względem 160-środka serca)

    m_healthBarForeground.setSize({300.f, 35.f});
    m_healthBarForeground.setFillColor(sf::Color::Red);
    m_healthBarForeground.setPosition({60.f, 145.f});

    m_healthText.setCharacterSize(25);
    m_healthText.setFillColor(sf::Color::White);
}

void InGameInterface::update(const Player& player)
{
    m_moneyText.setString(std::to_string(player.getMoney()));
    
    int currentHp = player.getHp();
    float hpPercentage = static_cast<float>(currentHp) / m_maxHp;
    if (hpPercentage < 0.f) hpPercentage = 0.f;
    
    m_healthBarForeground.setSize({300.f * hpPercentage, 35.f});
    
    std::string hpString = std::to_string(currentHp) + " HP";
    m_healthText.setString(hpString);

    // Centrowanie tekstu HP na pasku zdrowia
    sf::FloatRect textBounds = m_healthText.getLocalBounds();
    m_healthText.setPosition({
        60.f + (300.f - textBounds.size.x) / 2.f - textBounds.position.x,
        145.f + (35.f - textBounds.size.y) / 2.f - textBounds.position.y
    });
}

void InGameInterface::render(sf::RenderWindow& window) const
{
    window.draw(m_coinIcon);
    window.draw(m_moneyText);
    
    // Rysowanie paska pod sercem (pasek przysłonięty ikonką serca)
    window.draw(m_healthBarBackground);
    window.draw(m_healthBarForeground);
    window.draw(m_heartIcon);
    window.draw(m_healthText);
}
