#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <stdexcept>

class AssetManager
{
public:
    static AssetManager& getInstance();

    void loadTexture(const std::string& key, const std::string& filePath);
    const sf::Texture& getTexture(const std::string& key) const;

    void loadFont(const std::string& key, const std::string& filePath);
    const sf::Font& getFont(const std::string& key) const;

    void loadSoundBuffer(const std::string& key, const std::string& filePath);
    const sf::SoundBuffer& getSoundBuffer(const std::string& key) const;

    AssetManager(const AssetManager&)            = delete;
    AssetManager& operator=(const AssetManager&) = delete;

private:
    AssetManager() = default;

    std::map<std::string, sf::Texture>     m_textures;
    std::map<std::string, sf::Font>        m_fonts;
    std::map<std::string, sf::SoundBuffer> m_soundBuffers;
};
