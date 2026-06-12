#include "CreatureSpawner.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Random.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/Time.h>
#include <Engine/Core/Macros.h>

#include <Creatures/CreatureFactory.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>
#include <random>

void Game::CreatureSpawner::Update()
{
    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime >= m_SpawnInterval)
    {
        m_ElapsedTime -= m_SpawnInterval;

        auto& rng{ GameEngine::Random::GetRNG() };
        std::uniform_int_distribution<> distribution{ 0, 100 };
        int probabilityCheck{ distribution(rng) };

        DEBUG_CONSOLE("CreatureSpawner", std::to_string(probabilityCheck))

        if (probabilityCheck > m_Probability) return;

        int spawnBlockId{ m_SpawnBlockIds[rng() % m_SpawnBlockIds.size()] };
        auto spawnPosition{ m_pGraph->GetBlockSurfaceCenter(spawnBlockId, m_SpawnSurface) };

        auto& creature{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject()};
        CreatureFactory::BuildCreatureComponents(creature, m_CreatureType);
        creature.GetTransform()->SetLocalPosition(spawnPosition);

        m_SpawnedCreatures.push_back(&creature);
    }
}

void Game::CreatureSpawner::WipeSpawnedCreatures()
{
    for (auto creature : m_SpawnedCreatures)
    {
        creature->SetForDeletion();
    }
}

void Game::CreatureSpawner::Init(CreatureSpawnerInfo const& creatureSpawnerInfo)
{
    Init(creatureSpawnerInfo.CreatureType, creatureSpawnerInfo.SpawnInterval, creatureSpawnerInfo.SpawnProbability);
}

void Game::CreatureSpawner::Init(Creature creatureType, float spawnInterval, int spawnProbability)
{
    m_CreatureType = creatureType;
    m_SpawnInterval = spawnInterval;
    m_Probability = spawnProbability;

    switch (creatureType)
    {
    case Creature::Ugg:
        m_SpawnBlockIds = RIGHT_SPAWN_POINTS;
        break;
    case Creature::WrongWay:
        m_SpawnBlockIds = LEFT_SPAWN_POINTS;
        break;
    default:
        m_SpawnBlockIds = TOP_SPAWN_POINTS;
        break;
    }

    if (auto iter{ CreatureFactory::CREATURE_TABLE.find(creatureType) }; iter != CreatureFactory::CREATURE_TABLE.end())
    {
        m_SpawnSurface = iter->second.SpawnSurface;
    }
}

Game::CreatureSpawner::CreatureSpawner(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pGraph{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("Graph")->GetComponent<Graph>() }
{
}
