#include "SlimeController.h"

#include <Misc/Constants.h>
#include <Components/EnemySpawner.h>

#include <Engine/Core/SceneManager.h>

#include <utility>

void Game::SlimeController::Update()
{

}

void Game::SlimeController::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "EndOfPath")
    {
        // Spawn Coily
        auto coily{ Spawner::ConstructCoily() };
        coily->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetLocalPosition());
        GameEngine::SceneManager::Get().GetActiveScene()->Add(std::move(coily));
        GetOwner()->SetForDeletion();
    }
}

void Game::SlimeController::Init(Creature creatureType)
{
    switch (creatureType)
    {
    case Creature::PurpleSlime:
        SlimeFunctions::GenerateRandomPath(Consts::Enemy::MAX_PURPLE_SLIME_PATH_SIZE, m_Path);
        break;
    default:
        SlimeFunctions::GenerateRandomPath(Consts::Enemy::MAX_RED_GREEN_SLIME_PATH_SIZE, m_Path);
        break;
    }

    while (!m_Path.empty())
    {
        GetOwner()->SendEvent(std::move(m_Path.front()));
        m_Path.pop();
    }
}

Game::SlimeController::SlimeController(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
