#include "CoilyController.h"

#include <Components/Scenes/GameplaySettingsComponent.h>
#include <Events/EventArgMove.h>
#include <Misc/Enums.h>
#include <Misc/GlobalGameSettings.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>

GameEngine::GameObject* Game::CoilyController::GetQBertObject() const
{
    auto gameSettingsObj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("GameplaySettings") };

    if (gameSettingsObj)
    {
        auto player1Obj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("Player1") };
        auto player2Obj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("Player2") };

        switch (GlobalGameSettings::SelectedGamemode)
        {
        case Gamemode::Solo:
        case Gamemode::Versus:
            return player1Obj;
        case Gamemode::Coop:
            if (player1Obj == nullptr and player2Obj == nullptr) return nullptr;
            else if (player1Obj == nullptr) return player2Obj;
            else if (player2Obj == nullptr) return player1Obj;

            auto coilyPosition{ GetOwner()->GetTransform()->GetWorldPosition() };
            auto player1Distance{ glm::distance(coilyPosition, player1Obj->GetTransform()->GetWorldPosition()) };
            auto player2Distance{ glm::distance(coilyPosition, player2Obj->GetTransform()->GetWorldPosition()) };

            return (player1Distance < player2Distance) ? player1Obj : player2Obj;
        }
    }

    return nullptr;
}

void Game::CoilyController::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "IdleWaitExit")
    {
        MoveTowardsQBert();
    }
}

void Game::CoilyController::MoveTowardsQBert()
{
    auto qBertObj{ GetQBertObject() };
    if (qBertObj == nullptr) return;

    auto objPos{ GetOwner()->GetTransform()->GetWorldPosition() };
    auto qbertPos{ qBertObj->GetTransform()->GetWorldPosition() };

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
}
