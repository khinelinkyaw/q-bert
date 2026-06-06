#include "SlimeController.h"

#include <Components/BaseCreature.h>
#include <Components/EnemySpawner.h>
#include <Misc/Constants.h>
#include <Misc/Enums.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>

#include <utility>

void Game::GenericEnemyController::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "EndOfPath")
    {
        // Spawn Coily
        //auto& coily{ Spawner::ConstructCoily() };
        //coily.GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetLocalPosition());
        GetOwner()->SetForDeletion();
    }
}

void Game::GenericEnemyController::Init(Creature creatureType)
{
    switch (creatureType)
    {
    case Creature::PurpleSlime:
        EnemyFunctions::GenerateRandomPath(Consts::Enemy::MAX_PURPLE_SLIME_PATH_SIZE, m_Path, { Direction::DownLeft, Direction::DownRight });
        break;
    case Creature::GreenSlime:
    case Creature::RedSlime:
        EnemyFunctions::GenerateRandomPath(Consts::Enemy::MAX_NORMAL_ENEMY_PATH_SIZE, m_Path, { Direction::DownLeft, Direction::DownRight });
        break;
    case Creature::WrongWay:
        EnemyFunctions::GenerateRandomPath(Consts::Enemy::MAX_NORMAL_ENEMY_PATH_SIZE, m_Path, { Direction::UpLeft, Direction::DownLeft });
        break;
    case Creature::Ugg:
        EnemyFunctions::GenerateRandomPath(Consts::Enemy::MAX_NORMAL_ENEMY_PATH_SIZE, m_Path, { Direction::UpRight, Direction::DownRight });
        break;
    }

    while (!m_Path.empty())
    {
        GetOwner()->SendEvent(std::move(m_Path.front()));
        m_Path.pop();
    }
}

Game::GenericEnemyController::GenericEnemyController(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
