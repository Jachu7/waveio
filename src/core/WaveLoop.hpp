#pragma once
#include "entities/Enemy.hpp"
#include "entities/enemies/GreenSlime.hpp"
#include "entities/enemies/RedSlime.hpp"
#include "Constants.hpp"
#include <vector>
#include <memory>
#include <random>
#include <functional>

class WaveLoop
{
public:
    WaveLoop();
    void WaveSystem(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies);
    bool isWaveComplete() const { return waveComplete; }
    void startNextWave();
    int getWaveNumber() const { return waveNumber; }
private:
    float m_spawnTimer;
    int spawnedSingleWave;
    int waveNumber;
    bool waveComplete;
    std::random_device m_rd;
    std::mt19937 m_mt;
    std::uniform_real_distribution<float> m_dist_x;
    std::uniform_real_distribution<float> m_dist_y;

    // 1. Array of enemy types (registry of factories)
    std::vector<std::function<std::unique_ptr<Enemy>(sf::Vector2f)>> m_enemyRegistry;

    // 2. 2D array representing every wave with indexes into the registry
    std::vector<std::vector<int>> m_waveDefinitions;
};