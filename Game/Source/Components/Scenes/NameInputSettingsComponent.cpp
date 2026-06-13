#include "NameInputSettingsComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Components/SpriteFontComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>

#include <Components/Controllers/GeneralInputControllerComponent.h>
#include <Components/ScoreboardComponent.h>
#include <Misc/GlobalGameSettings.h>

#include <algorithm>
#include <string>

void Game::NameInputSettingsComponent::MoveIndicators(int increment)
{
    auto letterWidth{ m_NameTextObj->GetComponent<GameEngine::TextureComponent>()->GetSourceRect().width };

    m_CurrentLetterIndex = std::clamp(m_CurrentLetterIndex + increment, 0, static_cast<int>(m_CurrentName.size() - 1));

    auto startingPositionX{ m_NameTextObj->GetTransform()->GetWorldPosition().x };
    startingPositionX += (letterWidth * m_CurrentLetterIndex);

    for (auto const& indicator : m_CurrentLetterIndicators)
    {
        indicator->GetTransform()->SetWorldX(startingPositionX);
    }
}

void Game::NameInputSettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnSelectorLeft")
    {
        MoveIndicators(-1);
    }
    else if (eventArg->EventId == "OnSelectorRight")
    {
        MoveIndicators(1);
    }
    else if (eventArg->EventId == "OnSelectorDown")
    {
        if (m_CurrentName[m_CurrentLetterIndex] == ' ') { m_CurrentName[m_CurrentLetterIndex] = 'A'; }
        else m_CurrentName[m_CurrentLetterIndex] = (m_CurrentName[m_CurrentLetterIndex] == 'Z') ? ' ' : static_cast<char>(m_CurrentName[m_CurrentLetterIndex] + 1);
        m_NameTextObj->GetComponent<GameEngine::SpriteFontComponent>()->SetText(m_CurrentName);
    }
    else if (eventArg->EventId == "OnSelectorUp")
    {
        if (m_CurrentName[m_CurrentLetterIndex] == ' ') { m_CurrentName[m_CurrentLetterIndex] = 'Z'; }
        else m_CurrentName[m_CurrentLetterIndex] = (m_CurrentName[m_CurrentLetterIndex] == 'A') ? ' ' : static_cast<char>(m_CurrentName[m_CurrentLetterIndex] - 1);
        m_NameTextObj->GetComponent<GameEngine::SpriteFontComponent>()->SetText(m_CurrentName);
    }
    else if (eventArg->EventId == "OnSelectorConfirm")
    {
        GetOwner()->GetComponent<ScoreboardComponent>()->UpdateScore(m_CurrentName, GlobalGameSettings::PlayerScore);
        GameEngine::SceneManager::Get().SetActiveScene("HighScore");
    }
}

void Game::NameInputSettingsComponent::OnSceneLoad()
{
    auto scoreNumElement{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("ScoreNumUIElement") };
    scoreNumElement->GetComponent<GameEngine::SpriteFontComponent>()->SetText(std::to_string(GlobalGameSettings::PlayerScore));
}

Game::NameInputSettingsComponent::NameInputSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    m_NameTextObj->GetComponent<GameEngine::SpriteFontComponent>()->SetText(m_CurrentName);
    owner->AddComponent<GeneralInputController>();
    owner->AddComponent<ScoreboardComponent>();
}
