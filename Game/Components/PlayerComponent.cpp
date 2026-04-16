#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>
#include <Game/Components/PlayerComponent.h>

#include <string>

void Game::PlayerComponent::CheckHealth()
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

Game::PlayerComponent::PlayerComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_IsDead{ false }
    , m_Health{ }
    , m_MaxHealth{}
    , m_Score{}
    , m_Name{""}
    , m_pObservers{}
{
    CheckHealth();
}

void Game::PlayerComponent::TakeDamage()
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

void Game::PlayerComponent::Heal()
{
    ++m_Health;

    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }

    NotifyObservers("UpdateHealth");
}

int Game::PlayerComponent::GetHealth() const
{
    return m_Health;
}

void Game::PlayerComponent::SetMaxHealth(int newMaxHealth)
{
    m_MaxHealth = newMaxHealth;

    CheckHealth();
}

void Game::PlayerComponent::Revive(int newHealth)
{
    m_Health = newHealth;

    CheckHealth();
}

void Game::PlayerComponent::Revive()
{
    Revive(m_MaxHealth);
}

bool Game::PlayerComponent::IsDead() const
{
    return m_IsDead;
}

void Game::PlayerComponent::SetName(std::string const& name)
{
    m_Name = name;
}

std::string Game::PlayerComponent::GetName() const
{
    return m_Name;
}

int Game::PlayerComponent::GetScore() const
{
    return m_Score;
}

void Game::PlayerComponent::IncrementScore(int increment)
{
    m_Score += increment;

    if (m_Score < 0)
    {
        m_Score = 0;
    }
    else if (m_Score > 100)
    {
        NotifyObservers("FirstAchievement");
    }

    NotifyObservers("UpdateScore");
}

void Game::PlayerComponent::AddObserver(GameEngine::Observer* pObserver)
{
    m_pObservers.push_back(pObserver);
}

void Game::PlayerComponent::NotifyObservers(std::string eventId)
{
    for (auto pObserver : m_pObservers)
    {
        pObserver->OnNotify(*GetOwnerObject(), eventId);
    }
}

void Game::PlayerComponent::Init(int health, int maxHealth)
{
    m_Health = health;
    m_MaxHealth = maxHealth;

    NotifyObservers("UpdateHealth");
}
