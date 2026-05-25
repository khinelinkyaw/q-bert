#include "Breed.h"

#include <Map/Block.h>
#include <Map/Graph.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>

void Game::QBertBreed::OnNewBlock(Block* block)
{
    block->CycleType();
}

void Game::QBertBreed::OnEmptyBlock(GameEngine::GameObject& object, Graph const& graph)
{
    object.GetTransform()->SetLocalPosition(graph.GetBlockSurfaceCenter(0));
}

Game::QBertBreed::QBertBreed(GameEngine::GameObject* owner)
{
    GameEngine::SceneManager::Get().GetActiveScene()->SetObjectName("Qbert", owner->GetId());
}

void Game::EnemyBreed::OnEmptyBlock(GameEngine::GameObject& object, Graph const& )
{
    object.SetForDeletion();
}
