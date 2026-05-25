#include "EnemySpawner.h"

#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>

#include <Components/BaseCreature.h>
#include <Components/Controllers/CoilyController.h>

GameEngine::GameObject& Game::Spawner::ConstructCoily()
{
    GameEngine::GameObject& coily{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    coily.AddComponent<BaseCreature>()->Init(Creature::Coily);
    coily.AddComponent<CoilyController>();
    return coily;
}
