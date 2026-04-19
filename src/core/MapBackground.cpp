#include "MapBackground.hpp"
#include "AssetManager.hpp"

MapBackground::MapBackground()
    : m_sprite(AssetManager::getInstance().getTexture("mapa"))
{
}

void MapBackground::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
