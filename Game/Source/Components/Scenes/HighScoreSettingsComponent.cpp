#include "HighScoreSettingsComponent.h"

#include <Components/Controllers/GeneralInputControllerComponent.h>
#include <Components/ScoreboardComponent.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>

#include <algorithm>
#include <string>
#include <utility>
#include <Components/SpriteFontComponent.h>

void Game::HighScoreSettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnSelectorConfirm")
    {
        GameEngine::SceneManager::Get().SetActiveScene("Gameplay");
    }
}

void Game::HighScoreSettingsComponent::OnSceneLoad()
{
    auto playerScores{ GetOwner()->GetComponent<ScoreboardComponent>()->GetPlayerScores() };

    std::ranges::sort(playerScores, [](PlayerScorePair const& a, PlayerScorePair const& b) { return a.second > b.second; });

    std::string scoreText{};

    for (size_t index{ 0 }; index < 5 and index < playerScores.size(); ++index)
    {
        scoreText += playerScores[index].first+ " " + std::to_string(playerScores[index].second) + "\n";
    }

    m_ScoreboardTextObj->GetComponent<SpriteFontComponent>()->SetText(scoreText);
}

Game::HighScoreSettingsComponent::HighScoreSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
    owner->AddComponent<ScoreboardComponent>();
}
