#include "GameOverSceneComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Core/GameObject.h>

#include <Components/Controllers/GeneralInputControllerComponent.h>

#include <algorithm>
#include <Components/Controllers/GeneralInputControllerComponent.h>

void Game::GameOverSceneComponent::MoveSelector(int increment)
{
    m_Selection = std::clamp(m_Selection + increment, 0, (static_cast<int>(m_SelectionElements.size()) - 1));

    auto uiObj { m_SelectionElements[m_Selection].second };
    m_pSelector->GetTransform()->SetWorldY(uiObj->GetTransform()->GetWorldPosition().y);
}

void Game::GameOverSceneComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnSelectorUp")
    {
        MoveSelector(-1);
    }
    else if (eventArg->EventId == "OnSelectorDown")
    {
        MoveSelector(1);
    }
    else if (eventArg->EventId == "OnSelectorConfirm")
    {
        auto gameOverSelection { m_SelectionElements[m_Selection].first };

        switch (gameOverSelection)
        {
            case GameOverSelections::TryAgain:
            {
                GameEngine::SceneManager::Get().SetActiveScene("Gameplay");
                break;
            }
            case GameOverSelections::HighScore:
            {
                GameEngine::SceneManager::Get().SetActiveScene("HighScore");
                break;
            }
        }
    }
}

Game::GameOverSceneComponent::GameOverSceneComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
}
