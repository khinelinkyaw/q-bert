#include "ScoreCounterComponent.h"

#include <Components/SpriteFontComponent.h>
#include <Misc/Enums.h>
#include <UserInterface/UIEngine.h>

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
        m_pPlayerScoreTextComponent->UpdateText(std::to_string(scoreUpdateEventArg->Value));
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
    }
    
    if (gameObj) m_pPlayerScoreTextComponent = gameObj->GetComponent<SpriteFontComponent>();

    assert(m_pPlayerScoreTextComponent != nullptr);
}

Game::ScoreCounterComponent::ScoreCounterComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
}
