#include "Breed.h"

#include <Creatures/CreatureFactory.h>
#include <Misc/Enums.h>
#include <Map/Block.h>
#include <Map/Graph.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArgInt.h>

void Game::Breed::DecreaseLive(GameEngine::GameObject& object)
{
    --m_CreatureInfo.Lives;

    if (m_CreatureInfo.Lives <= 0)
    {
        object.SetForDeletion();
    }
    else
    {
        auto graph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() };
        object.GetTransform()->SetLocalPosition(graph->GetBlockSurfaceCenter(0, BlockSurface::Top));
    }
}

void Game::Breed::IncreaseScore(int increment, GameEngine::GameObject& object)
{
    m_CreatureInfo.Score += increment;
    object.SendEvent<GameEngine::EventArgInt>("PlayerScoreUpdated", m_CreatureInfo.Score);
}

void Game::Breed::OnEmptyBlock(GameEngine::GameObject& object)
{
    object.SetForDeletion();
}

void Game::QBertBreed::OnNewBlock(GameEngine::GameObject& object, Block* block)
{
    block->ForwardBlockType();
    IncreaseScore(25, object);
}

void Game::QBertBreed::OnEmptyBlock(GameEngine::GameObject& object)
{
    DecreaseLive(object);
}

void Game::QBertBreed::OnCollision(GameEngine::GameObject& object, Weakness attacker)
{
    switch (attacker)
    {
    case Weakness::None:
        DecreaseLive(object);
        break;
    case Weakness::Qbert:
        IncreaseScore(300, object);
        break;
    }
}

Game::QBertBreed::QBertBreed(GameEngine::GameObject* owner)
    : Breed{Weakness::NormalEnemy}
{
    GameEngine::SceneManager::Get().GetActiveScene()->SetObjectName("Qbert", owner->GetId());
}

void Game::PurpleSlimeBreed::OnEndOfPath(GameEngine::GameObject& object)
{
    // Spawn Coily
    auto& coily{ GameEngine::SceneManager::Get().GetActiveScene()->CreateGameObject() };
    CreatureFactory::BuildCreatureComponents(coily, Creature::Coily);
    coily.GetTransform()->SetLocalPosition(object.GetTransform()->GetLocalPosition());
    object.SetForDeletion();
}

void Game::GreenEnemyBreed::OnCollision(GameEngine::GameObject& object, Weakness attacker)
{
    switch (attacker)
    {
    case Weakness::NormalEnemy:
        DecreaseLive(object);
        break;
    }
}

void Game::GreenEnemyBreed::OnNewBlock(GameEngine::GameObject&, Block* block)
{
    block->ReverseBlockType();
}
