#include "EnemySpawner.h"

#include <Engine/Animation/Animation.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Components/BaseComponent.h>

#include <Components/BaseCreature.h>
#include <Components/Controllers/ControllerComponent.h>
#include <Components/Controllers/CoilyController.h>
#include <Components/Controllers/SlimeController.h>
#include <Map/Graph.h>

GameEngine::GameObject& Game::CreatureSpawner::ConstructCoily(int graphBlockId)
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    object.GetTransform()->SetLocalPosition(m_pGraph->GetBlockSurfaceCenter(graphBlockId, BlockSurface::Top));
    object.AddComponent<GameEngine::SpriteComponent>()->Init("Coily.png", 1, 8);
    object.AddComponent<BaseCreature>()->Init(Creature::Coily);
    object.AddComponent<CoilyController>();
    object.AddComponent<GameEngine::CollisionComponent>();
    object.GetComponent<GameEngine::TextureComponent>()->SetPivot(GameEngine::Pivot::MiddleDown);
    return object;
}

GameEngine::GameObject& Game::CreatureSpawner::ConstructPurpleSlime(int graphBlockId)
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    object.GetTransform()->SetLocalPosition(m_pGraph->GetBlockSurfaceCenter(graphBlockId, BlockSurface::Top));
    object.AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
    object.AddComponent<BaseCreature>()->Init(Creature::PurpleSlime);
    object.AddComponent<GenericEnemyController>()->Init(Creature::PurpleSlime);
    object.AddComponent<GameEngine::CollisionComponent>();
    object.GetComponent<GameEngine::TextureComponent>()->SetPivot(GameEngine::Pivot::MiddleDown);
    return object;
}

GameEngine::GameObject& Game::CreatureSpawner::ConstructGreenSlime(int graphBlockId)
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    object.GetTransform()->SetLocalPosition(m_pGraph->GetBlockSurfaceCenter(graphBlockId, BlockSurface::Top));
    object.AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
    object.AddComponent<BaseCreature>()->Init(Creature::GreenSlime);
    object.AddComponent<GenericEnemyController>()->Init(Creature::GreenSlime);
    object.AddComponent<GameEngine::CollisionComponent>();
    object.GetComponent<GameEngine::TextureComponent>()->SetPivot(GameEngine::Pivot::MiddleDown);
    return object;
}

GameEngine::GameObject& Game::CreatureSpawner::ConstructRedSlime(int graphBlockId)
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    object.GetTransform()->SetLocalPosition(m_pGraph->GetBlockSurfaceCenter(graphBlockId, BlockSurface::Top));
    object.AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
    object.AddComponent<BaseCreature>()->Init(Creature::RedSlime);
    object.AddComponent<GenericEnemyController>()->Init(Creature::RedSlime);
    object.AddComponent<GameEngine::CollisionComponent>();
    object.GetComponent<GameEngine::TextureComponent>()->SetPivot(GameEngine::Pivot::MiddleDown);
    return object;
}

Game::CreatureSpawner::CreatureSpawner(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pGraph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() }
{
}

void Game::Builder::AddCommonComponents(GameEngine::GameObject& gameObject, GameEngine::Pivot pivot)
{
    gameObject.AddComponent<GameEngine::CollisionComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>();
    gameObject.AddComponent<BaseCreature>();
    gameObject.AddComponent<GameEngine::TextureComponent>()->SetPivot(pivot);
}

void Game::Builder::InitQBertComponents(GameEngine::GameObject& gameObject)
{
    gameObject.AddComponent<ControllerComponent>();

    gameObject.GetComponent<GameEngine::SpriteComponent>()->Init("Qbert.png", 1, 8);
    gameObject.GetComponent<BaseCreature>()->Init(Creature::QBert);
}

void Game::Builder::InitSlimeComponents(GameEngine::GameObject& gameObject, Creature creatureType)
{
    gameObject.AddComponent<GenericEnemyController>()->Init(creatureType);

    gameObject.GetComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
    gameObject.GetComponent<BaseCreature>()->Init(creatureType);
}

void Game::Builder::InitCoilyComponents(GameEngine::GameObject& gameObject)
{
    gameObject.AddComponent<CoilyController>();

    gameObject.GetComponent<GameEngine::SpriteComponent>()->Init("Coily.png", 1, 8);
    gameObject.GetComponent<BaseCreature>()->Init(Creature::Coily);
}

GameEngine::GameObject& Game::Builder::BuildQBert()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object, GameEngine::Pivot::MiddleDown);
    InitQBertComponents(object);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildCoily()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object);
    InitCoilyComponents(object);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildPurpleSlime()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object);
    InitSlimeComponents(object, Creature::PurpleSlime);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildGreenSlime()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object);
    InitSlimeComponents(object, Creature::GreenSlime);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildRedSlime()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object);
    InitSlimeComponents(object, Creature::RedSlime);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildUgg()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object, GameEngine::Pivot::LeftUp);
    object.GetComponent<GameEngine::TextureComponent>()->SetOriginOffset({2.f, 2.f});
    object.AddComponent<GenericEnemyController>()->Init(Creature::Ugg);
    object.GetComponent<GameEngine::SpriteComponent>()->Init("Ugg.png", 1, 8);
    object.GetComponent<BaseCreature>()->Init(Creature::Ugg);
    return object;
}

GameEngine::GameObject& Game::Builder::BuildWrongWay()
{
    GameEngine::GameObject& object{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    AddCommonComponents(object, GameEngine::Pivot::RightUp);
    object.GetComponent<GameEngine::TextureComponent>()->SetOriginOffset({ -2.f, 2.f });
    object.AddComponent<GenericEnemyController>()->Init(Creature::WrongWay);
    object.GetComponent<GameEngine::SpriteComponent>()->Init("Wrongway.png", 1, 8);
    object.GetComponent<BaseCreature>()->Init(Creature::WrongWay);
    return object;
}
