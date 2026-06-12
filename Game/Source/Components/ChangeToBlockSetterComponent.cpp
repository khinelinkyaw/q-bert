#include "ChangeToBlockSetterComponent.h"

#include <Engine/Events/EventArgInt.h>

void Game::ChangeToBlockSetterComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "SetChangeToBlock")
    {
        auto setChangeToBlockEventArg{ static_cast<GameEngine::EventArgInt*>(eventArg) };
        m_pSpriteComponent->SetSpriteIndex(setChangeToBlockEventArg->Value);
    }
}

Game::ChangeToBlockSetterComponent::ChangeToBlockSetterComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
