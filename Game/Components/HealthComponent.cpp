#include "HealthComponent.h"

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
    else if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}

void Game::HealthComponent::FixedUpdate()
{
}

void Game::HealthComponent::Update()
{
}

void Game::HealthComponent::Render(glm::vec3 const&) const
{
}

Game::HealthComponent::HealthComponent(int health, int maxHealth)
    : m_IsDead{ false }
    , m_Health{ health }
    , m_MaxHealth{ maxHealth }
{
    CheckHealth();
}

void Game::HealthComponent::TakeDamage(unsigned int damage)
{
    m_Health -= damage;

    CheckHealth();
}

void Game::HealthComponent::Heal(unsigned int addedHealth)
{
    m_Health += addedHealth;

    CheckHealth();
}

int Game::HealthComponent::GetHealth() const
{
    return m_Health;
}

void Game::HealthComponent::SetMaxHealth(unsigned int newMaxHealth)
{
    m_MaxHealth = newMaxHealth;
}


void Game::HealthComponent::Revive(unsigned int newHealth)
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
