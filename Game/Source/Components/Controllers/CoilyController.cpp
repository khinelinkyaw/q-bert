#include "CoilyController.h"

#include <Events/EventArgMove.h>
#include <Misc/Enums.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <cassert>

void Game::CoilyController::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "IdleWaitExit")
    {
        MoveTowardsQBert();
    }
}

void Game::CoilyController::MoveTowardsQBert()
{
    auto objPos{ GetOwner()->GetTransform()->GetWorldPosition() };
    auto qbertPos{ m_pQBertObject->GetTransform()->GetWorldPosition() };

    Direction direction{};

    // DownRight
    if (qbertPos.x > objPos.x and qbertPos.y > objPos.y)
    {
        direction = Direction::DownRight;
    }
    // DownLeft
    else if (qbertPos.x <= objPos.x and qbertPos.y > objPos.y)
    {
        direction = Direction::DownLeft;
    }
    // UpRight
    else if (qbertPos.x > objPos.x and qbertPos.y <= objPos.y)
    {
        direction = Direction::UpRight;
    }
    // UpLeft
    else if (qbertPos.x <= objPos.x and qbertPos.y <= objPos.y)
    {
        direction = Direction::UpLeft;
    }

    GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, direction);
    GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnIdleWait, direction);
}

Game::CoilyController::CoilyController(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    m_pQBertObject = GameEngine::SceneManager::Get().GetObjectByName("Qbert");
    assert(m_pQBertObject != nullptr);
}
