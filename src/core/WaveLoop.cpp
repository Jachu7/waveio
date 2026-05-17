#include "WaveLoop.hpp"

WaveLoop::WaveLoop()
    : m_spawnTimer(0.f)
    , spawnedSingleWave(0)
    , waveNumber(1)
    , waveComplete(false)
    , m_mt(m_rd())
    , m_dist_x(0.f, MAP_WIDTH)
    , m_dist_y(0.f, MAP_HEIGHT)
{
    // 1. Array of enemy types (the registry)
    // Index 0: GreenSlime, Index 1: RedSlime
    m_enemyRegistry = {
        [](sf::Vector2f pos) { return std::make_unique<GreenSlime>(pos); },
        [](sf::Vector2f pos) { return std::make_unique<RedSlime>(pos); }
    };

    // 2. 2D array representing every wave with indexes
    m_waveDefinitions = {
        {0},          // Wave 1: Only GreenSlime (index 0)
        {0, 0, 1},    // Wave 2: Mostly Green, some Red
        {0, 1},       // Wave 3: Even mix
        {0, 1, 1},    // Wave 4: Mostly Red
        {1}           // Wave 5+: Only Red
    };
}

void WaveLoop::startNextWave()
{
    spawnedSingleWave = 0;
    waveComplete = false;
    waveNumber++;
}

void WaveLoop::WaveSystem(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    if (waveComplete) return;

    int waveSize = 10 + (waveNumber * 2);

    if (spawnedSingleWave < waveSize)//Spawning enemies till waveSize is reached
    {
        m_spawnTimer += deltaTime;
        if (m_spawnTimer >= 0.5f)//Spawn intervals
        {
            // Get the pool for the current wave, taking the last if we go over
            int waveIndex = std::min((int)waveNumber - 1, (int)m_waveDefinitions.size() - 1);
            const auto& currentWave = m_waveDefinitions[waveIndex];

            // Randomly select an index from the current wave's array
            std::uniform_int_distribution<int> type_dist(0, currentWave.size() - 1);
            int selectedEnemyId = currentWave[type_dist(m_mt)];
            
            sf::Vector2f spawnPos(m_dist_x(m_mt), m_dist_y(m_mt));
            
            // Create the enemy by choosing him from predefined registry
            enemies.push_back(m_enemyRegistry[selectedEnemyId](spawnPos));

            m_spawnTimer = 0.f;
            spawnedSingleWave++;
        }
    }
    else
    {
        if (enemies.empty())//If there's no enemies left, complete the wave
        {
            waveComplete = true;
        }
    }
}
