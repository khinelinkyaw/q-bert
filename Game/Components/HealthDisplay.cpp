#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Game/Components/HealthDisplay.h>
#include <Game/Components/PlayerComponent.h>

#include <cassert>
#include <format>
#include <string>

void Game::HealthDisplayObserver::OnNotify(GameEngine::GameObject&, std::string eventId)
{
    if (eventId == "UpdateHealth")
    {
        m_pTextComponent->SetText(std::format("{}: {}", m_PlayerName, m_pPlayerComponent->GetHealth()));
    }
    else if (eventId == "PlayerDied")
    {
        m_pTextComponent->SetText(std::format("{}: Dead!", m_PlayerName));
    }
}

void Game::HealthDisplayObserver::SetPlayerName(std::string const& prefix)
{
    m_PlayerName = prefix;
}

Game::HealthDisplayObserver::HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, PlayerComponent* pHealthComponent)
    : m_pTextComponent{ pTextComponent }
    , m_pPlayerComponent{ pHealthComponent }
    , m_PlayerName{}
{
    assert(m_pTextComponent != nullptr and m_pPlayerComponent != nullptr);
}
