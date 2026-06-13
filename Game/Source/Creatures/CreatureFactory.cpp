#include "CreatureFactory.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>

#include <Misc/Enums.h>

#include <Components/ScoreCounterComponent.h>
#include <Components/BaseCreature.h>
#include <Components/Controllers/CoilyController.h>
#include <Components/Controllers/ControllerComponent.h>
#include <Components/Controllers/GenericEnemyController.h>

void Game::CreatureFactory::BuildComputerController(Game::Creature creatureType, GameEngine::GameObject& gameObject)
{
    switch (creatureType)
    {
    case Creature::Coily:
        gameObject.AddComponent<CoilyController>();
        break;
    default:
        gameObject.AddComponent<GenericEnemyController>()->Init(creatureType);
        break;
    }
}

void Game::CreatureFactory::BuildCreatureComponents(GameEngine::GameObject& gameObject, Creature creatureType, PlayerIndex playerIndex)
{
    gameObject.AddComponent<GameEngine::CollisionComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>();
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<BaseCreature>();

    switch (playerIndex)
    {
    case PlayerIndex::None:
        BuildComputerController(creatureType, gameObject);
        break;
    default:
        gameObject.AddComponent<ControllerComponent>();
        gameObject.AddComponent<ScoreCounterComponent>()->Init(playerIndex);
        break;
    }

    if (auto iter{ CREATURE_TABLE.find(creatureType) }; iter != CREATURE_TABLE.end())
    {
        CreatureData const& data{ iter->second };
        gameObject.GetComponent<GameEngine::SpriteComponent>()->Init(data.SpritePath, data.SpriteRows, data.SpriteCols);
        gameObject.GetComponent<GameEngine::TextureComponent>()->SetPivot(data.Pivot);
        gameObject.GetComponent<GameEngine::TextureComponent>()->SetOriginOffset(data.PivotOffset);
    }

    gameObject.GetComponent<BaseCreature>()->Init(creatureType, playerIndex);
}
