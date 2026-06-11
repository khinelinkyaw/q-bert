#include "LevelDisplayComponent.h"

#include <Events/EventArgLevel.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>

void Game::LevelDisplayComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnNewRound")
    {
        auto newRoundEventArg{ static_cast<EventArgLevel*>(eventArg) };
        Init(
            static_cast<int>(newRoundEventArg->FinalBlockColor),
            newRoundEventArg->LevelIndex,
            newRoundEventArg->RoundIndex
        );
    }
}

void Game::LevelDisplayComponent::Init(int changeToBlockSpriteIndex, int levelNum, int roundNum)
{
    m_pChangeToBlockSprite->SetSpriteIndex(changeToBlockSpriteIndex);
    m_pLevelNumSpriteFont->UpdateNumber(levelNum);
    m_pRoundNumSpriteFont->UpdateNumber(roundNum);
}

Game::LevelDisplayComponent::LevelDisplayComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
