#include "CoilyController.h"

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Map/Block.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Decoupling/Event.h>

//#include <vector>

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

    LookDirection direction{};

    // If the qBert is vertical to Coily, Coily will go left
    // If the qBert is horizontal to Coily, Coily will go up

    // DownRight
    if (qbertPos.x > objPos.x and qbertPos.y > objPos.y)
    {
        direction = LookDirection::DownRight;
    }
    // DownLeft
    else if (qbertPos.x <= objPos.x and qbertPos.y > objPos.y)
    {
        direction = LookDirection::DownLeft;
    }
    // UpRight
    else if (qbertPos.x > objPos.x and qbertPos.y <= objPos.y)
    {
        direction = LookDirection::UpRight;
    }
    // UpLeft
    else if (qbertPos.x <= objPos.x and qbertPos.y <= objPos.y)
    {
        direction = LookDirection::UpLeft;
    }

    GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, direction);
    GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnIdleWait, direction);
}

//void Game::CoilyController::SetPath(std::vector<Block const*> const& path)
//{
//    for (int index{ 0 }; index < path.size() - 1; ++index)
//    {
//        auto fromBlockPos{ path[index]->GetPosition() };
//        auto toBlockPos{ path[index + 1]->GetPosition()};
//
//        LookDirection direction{};
//
//        // DownRight
//        if (toBlockPos.x > fromBlockPos.x and toBlockPos.y > fromBlockPos.y)
//        {
//            direction = LookDirection::DownRight;
//        }
//        // DownLeft
//        else if (toBlockPos.x < fromBlockPos.x and toBlockPos.y > fromBlockPos.y)
//        {
//            direction = LookDirection::DownLeft;
//        }
//        // UpRight
//        else if (toBlockPos.x > fromBlockPos.x and toBlockPos.y < fromBlockPos.y)
//        {
//            direction = LookDirection::UpRight;
//        }
//        // UpLeft
//        else if (toBlockPos.x < fromBlockPos.x and toBlockPos.y < fromBlockPos.y)
//        {
//            direction = LookDirection::UpLeft;
//        }
//
//        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnIdleWait, direction);
//        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, direction);
//    }
//}

Game::CoilyController::CoilyController(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    //GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>()->SendGraphEvent(GraphEvent::FindPathToQbert, GetOwner()->GetId());
    m_pQBertObject = GameEngine::SceneManager::Get().GetObjectByName("Qbert");
    assert(m_pQBertObject != nullptr);
}
