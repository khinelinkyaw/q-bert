#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Game/Components/HealthDisplay.h>
#include <Engine/Decoupling/Observer.h>

#include <cassert>
#include <format>
#include <string>


#pragma region HealthDisplayObserver
void Game::HealthDisplayObserver::OnNotify(GameEngine::GameObject&, std::string eventId)
{
    if (eventId == "UpdateHealth")
    {
        m_pTextComponent->SetText(std::format("{}: {}", m_PlayerName, m_pHealthComponent->GetHealth()));
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

Game::HealthDisplayObserver::HealthDisplayObserver(GameEngine::TextComponent* pTextComponent, HealthComponent* pHealthComponent)
    : m_pTextComponent{ pTextComponent }
    , m_pHealthComponent{ pHealthComponent }
    , m_PlayerName{}
{
    assert(m_pTextComponent != nullptr and m_pHealthComponent != nullptr);
}
#pragma endregion


#pragma region HealthComponent
void Game::HealthComponent::CheckHealth()
{
    if (m_Health <= 0)
    {
        m_IsDead = true;
        m_Health = 0;
    }
    else if (m_Health > 0 and m_IsDead == true)
    {
        m_IsDead = false;
    }

}

Game::HealthComponent::HealthComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
    , m_IsDead{ false }
    , m_Health{ }
    , m_MaxHealth{}
    , m_pObservers{}
{
    CheckHealth();
}

void Game::HealthComponent::TakeDamage()
{
    --m_Health;

    if (m_Health <= 0)
    {
        m_IsDead = true;
        m_Health = 0;
        NotifyObservers("PlayerDied");
    }
    else
    {
        NotifyObservers("UpdateHealth");
    }
}

void Game::HealthComponent::Heal()
{
    ++m_Health;

    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }

    NotifyObservers("UpdateHealth");
}

int Game::HealthComponent::GetHealth() const
{
    return m_Health;
}

void Game::HealthComponent::SetMaxHealth(int newMaxHealth)
{
    m_MaxHealth = newMaxHealth;

    CheckHealth();
}

void Game::HealthComponent::Revive(int newHealth)
{
    m_Health = newHealth;

    CheckHealth();
}

void Game::HealthComponent::Revive()
{
    Revive(m_MaxHealth);
}

bool Game::HealthComponent::IsDead() const
{
    return m_IsDead;
}
void Game::HealthComponent::AddObserver(GameEngine::Observer* pObserver)
{
    m_pObservers.push_back(pObserver);
}
void Game::HealthComponent::NotifyObservers(std::string eventId)
{
    for (auto pObserver : m_pObservers)
    {
        pObserver->OnNotify(*GetOwnerObject(), eventId);
    }
}
void Game::HealthComponent::Init(int health, int maxHealth)
{
    m_Health = health;
    m_MaxHealth = maxHealth;

    NotifyObservers("UpdateHealth");
}
#pragma endregion
