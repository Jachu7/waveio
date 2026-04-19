#include "AssetManager.hpp"

AssetManager& AssetManager::getInstance()
{
    static AssetManager instance;
    return instance;
}

void AssetManager::loadTexture(const std::string& key, const std::string& filePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath))
        throw std::runtime_error("AssetManager: nie mozna zaladowac tekstury: " + filePath);

    m_textures.emplace(key, std::move(texture));
}

const sf::Texture& AssetManager::getTexture(const std::string& key) const
{
    auto it = m_textures.find(key);
    if (it == m_textures.end())
        throw std::runtime_error("AssetManager: brak tekstury o kluczu: " + key);

    return it->second;
}

void AssetManager::loadFont(const std::string& key, const std::string& filePath)
{
    sf::Font font;
    if (!font.openFromFile(filePath))
        throw std::runtime_error("AssetManager: nie mozna zaladowac fontu: " + filePath);

    m_fonts.emplace(key, std::move(font));
}

const sf::Font& AssetManager::getFont(const std::string& key) const
{
    auto it = m_fonts.find(key);
    if (it == m_fonts.end())
        throw std::runtime_error("AssetManager: brak fontu o kluczu: " + key);

    return it->second;
}

void AssetManager::loadSoundBuffer(const std::string& key, const std::string& filePath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath))
        throw std::runtime_error("AssetManager: nie mozna zaladowac dzwieku: " + filePath);

    m_soundBuffers.emplace(key, std::move(buffer));
}

const sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& key) const
{
    auto it = m_soundBuffers.find(key);
    if (it == m_soundBuffers.end())
        throw std::runtime_error("AssetManager: brak dzwieku o kluczu: " + key);

    return it->second;
}
