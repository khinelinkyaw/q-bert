#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Game/Components/Observers.h>
#include <Game/Components/PlayerComponent.h>

#include <cassert>
#include <format>
#include <string>

void Game::HealthDisplayObserver::OnNotify(GameEngine::GameObject&, std::string eventId)
{
    if (eventId == "UpdateHealth")
    {
        m_pTextComponent->SetText(std::format("{}: {}", m_pPlayerComponent->GetName(), m_pPlayerComponent->GetHealth()));
    }
    else if (eventId == "PlayerDied")
    {
        m_pTextComponent->SetText(std::format("{} health: Dead!", m_pPlayerComponent->GetName()));
    }
}

Game::HealthDisplayObserver::HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pPlayerComponent)
    : m_pTextComponent{ pTextComponent }
    , m_pPlayerComponent{ pPlayerComponent }
{
    assert(m_pTextComponent != nullptr and m_pPlayerComponent != nullptr);
}

void Game::ScoreDisplayObserver::OnNotify(GameEngine::GameObject&, std::string eventId)
{
    if (eventId == "UpdateScore")
    {
        m_pTextComponent->SetText(std::format("{} score: {}", m_pPlayerComponent->GetName(), m_pPlayerComponent->GetScore()));
    }
}

Game::ScoreDisplayObserver::ScoreDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pPlayerComponent)
    : m_pTextComponent{ pTextComponent }
    , m_pPlayerComponent{ pPlayerComponent }
{
    assert(m_pTextComponent != nullptr and m_pPlayerComponent != nullptr);

    OnNotify(*pPlayerComponent->GetOwnerObject(), "UpdateScore");
}
