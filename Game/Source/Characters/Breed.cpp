#include "Breed.h"

#include <Map/Block.h>
#include <Map/Graph.h>

#include <Engine/Core/GameObject.h>

void Game::QBertBreed::OnNewBlock(Block* block)
{
    block->CycleType();
}

void Game::QBertBreed::OnEmptyBlock(GameEngine::GameObject& object, Graph const& graph)
{
    object.GetTransform()->SetLocalPosition(graph.GetBlockSurfaceCenter(0));
}

void Game::SlimeBreed::OnEmptyBlock(GameEngine::GameObject& object, Graph const& )
{
    void();
    object.SetForDeletion();
}