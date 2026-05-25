#include "EnemySpawner.h"

#include <Engine/Core/GameObject.h>

#include <Components/BaseCreature.h>
#include <Components/Controllers/CoilyController.h>

#include <memory>

std::unique_ptr<GameEngine::GameObject> Game::Spawner::ConstructCoily()
{
    std::unique_ptr<GameEngine::GameObject> coily{ std::make_unique<GameEngine::GameObject>() };
    coily->AddComponent<BaseCreature>()->Init(Creature::Coily);
    //coily->AddComponent<CoilyController>();
    return coily;
}
