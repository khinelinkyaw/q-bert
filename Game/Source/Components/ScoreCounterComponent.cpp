#include "ScoreCounterComponent.h"

#include <Misc/Enums.h>
#include <Misc/GlobalGameSettings.h>
#include <Misc/Constants.h>

#include <Engine/Components/SpriteFontComponent.h>
#include <Engine/UI/UIEngine.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Events/EventArgInt.h>

#include <cassert>
#include <string>

void Game::ScoreCounterComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "PlayerScoreUpdated")
    {
        auto scoreUpdateEventArg{ static_cast<GameEngine::EventArgInt*>(eventArg) };
        m_pPlayerScoreTextComponent->SetText(std::to_string(scoreUpdateEventArg->Value));

        if (GlobalGameSettings::PlayerScore < scoreUpdateEventArg->Value)
        {
            GlobalGameSettings::PlayerScore = scoreUpdateEventArg->Value;
        }
    }
}

void Game::ScoreCounterComponent::Init(PlayerIndex playerIndex)
{
    GameEngine::GameObject* gameObj{};

    switch (playerIndex)
    {
    case PlayerIndex::Player1:
        gameObj = GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::PLAYER_1_SCORE_ELEMENT);
        break;
    case PlayerIndex::Player2:
        gameObj = GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::PLAYER_2_SCORE_ELEMENT);
        break;
    default:
        break;
    }
    
    if (gameObj) m_pPlayerScoreTextComponent = gameObj->GetComponent<GameEngine::SpriteFontComponent>();

    assert(m_pPlayerScoreTextComponent != nullptr);
}

Game::ScoreCounterComponent::ScoreCounterComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
}
