#include "CreatureSpawner.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Random.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/Time.h>

#include <Components/BaseCreature.h>
#include <Creatures/CreatureFactory.h>
#include <Map/Graph.h>

void Game::CreatureSpawner::Update()
{
    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime >= m_SpawnInterval)
    {
        m_ElapsedTime -= m_SpawnInterval;

        auto& rng{ GameEngine::Random::GetRNG() };
        int spawnBlockId{ m_SpawnBlockIds[rng() % m_SpawnBlockIds.size()] };
        auto spawnPosition{ m_pGraph->GetBlockSurfaceCenter(spawnBlockId, m_SpawnSurface) };

        auto& creature{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject()};
        CreatureFactory::BuildCreatureComponents(creature, m_CreatureType);
        creature.GetTransform()->SetLocalPosition(spawnPosition);
    }
}

void Game::CreatureSpawner::Init(Creature creatureType, float spawnInterval)
{
    m_CreatureType = creatureType;
    m_SpawnInterval = spawnInterval;

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
    , m_pGraph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() }
{
}
