#include "CreatureFactory.h"

#include <Engine/Animation/Animation.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Random.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/Time.h>
#include <Engine/Misc/Enums.h>

#include <Components/BaseCreature.h>
#include <Components/Controllers/CoilyController.h>
#include <Components/Controllers/ControllerComponent.h>
#include <Components/Controllers/GenericEnemyController.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>

void Game::CreatureFactory::BuildCreatureController(Game::Creature creatureType, GameEngine::GameObject& gameObject)
{
    switch (creatureType)
    {
    case Creature::QBert:
        gameObject.AddComponent<ControllerComponent>();
        break;
    case Creature::Coily:
        gameObject.AddComponent<CoilyController>();
        break;
    default:
        gameObject.AddComponent<GenericEnemyController>()->Init(creatureType);
        break;
    }
}

void Game::CreatureFactory::BuildCreatureComponents(GameEngine::GameObject& gameObject, Creature creatureType)
{
    gameObject.AddComponent<GameEngine::CollisionComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>();
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<BaseCreature>();

    BuildCreatureController(creatureType, gameObject);

    if (auto iter{ CREATURE_TABLE.find(creatureType) }; iter != CREATURE_TABLE.end())
    {
        CreatureData const& data{ iter->second };
        gameObject.GetComponent<GameEngine::SpriteComponent>()->Init(data.SpritePath, data.SpriteRows, data.SpriteCols);
        gameObject.GetComponent<GameEngine::TextureComponent>()->SetPivot(data.Pivot);
        gameObject.GetComponent<GameEngine::TextureComponent>()->SetOriginOffset(data.PivotOffset);
    }

    gameObject.GetComponent<BaseCreature>()->Init(creatureType);
}
