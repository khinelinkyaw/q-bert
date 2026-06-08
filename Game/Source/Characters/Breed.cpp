#include "Breed.h"

#include <Creatures/CreatureFactory.h>
#include <Components/BaseCreature.h>
#include <Map/Block.h>
#include <Map/Graph.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>

void Game::QBertBreed::OnNewBlock(Block* block)
{
    block->CycleType();
}

void Game::QBertBreed::OnEmptyBlock(GameEngine::GameObject& object)
{
    // This won't be used later, the QBert will die ofc
    auto graph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() };
    object.GetTransform()->SetLocalPosition(graph->GetBlockSurfaceCenter(0, BlockSurface::Top));
}

Game::QBertBreed::QBertBreed(GameEngine::GameObject* owner)
{
    GameEngine::SceneManager::Get().GetActiveScene()->SetObjectName("Qbert", owner->GetId());
}

void Game::EnemyBreed::OnEmptyBlock(GameEngine::GameObject& object)
{
    object.SetForDeletion();
}

void Game::PurpleSlimeBreed::OnEndOfPath(GameEngine::GameObject& object)
{
    // Spawn Coily
    auto& coily{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    CreatureFactory::BuildCreatureComponents(coily, Creature::Coily);
    coily.GetTransform()->SetLocalPosition(object.GetTransform()->GetLocalPosition());
    object.SetForDeletion();
}
