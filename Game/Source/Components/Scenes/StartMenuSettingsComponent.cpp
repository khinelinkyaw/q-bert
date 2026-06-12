#include "StartMenuSettingsComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>

#include <Misc/GlobalGameSettings.h>
#include <algorithm>
#include <Components/Controllers/GeneralInputControllerComponent.h>

void Game::StartMenuSettingsComponent::MoveSelector(int increment)
{
    m_Selection = std::clamp(m_Selection + increment, 0, (static_cast<int>(m_SelectionElements.size()) - 1));

    auto uiObj{ m_SelectionElements[m_Selection].second };
    m_pSelector->GetTransform()->SetWorldY(uiObj->GetTransform()->GetWorldPosition().y);
}

void Game::StartMenuSettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
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
        GlobalGameSettings::SelectedGamemode = m_SelectionElements[m_Selection].first;
        GameEngine::SceneManager::Get().SetActiveScene("Gameplay");
     }
}

Game::StartMenuSettingsComponent::StartMenuSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
    owner->AddComponent<GeneralInputController>();
}

