#include "ScoreCounterComponent.h"

#include <Engine/Events/EventArgInt.h>

void Game::ScoreCounterComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "PlayerScoreUpdated")
    {
        auto scoreUpdateEventArg{ static_cast<GameEngine::EventArgInt*>(eventArg) };
        m_pScoreTextComponent->UpdateNumber(scoreUpdateEventArg->Value);
    }
}

Game::ScoreCounterComponent::ScoreCounterComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
    assert(m_pScoreTextComponent != nullptr);
}
