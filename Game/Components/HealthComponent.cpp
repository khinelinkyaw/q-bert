#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/MessageQueue.h>
#include <Game/Components/HealthComponent.h>

void Game::HealthComponent::CheckHealth()
{
    if (m_Health <= 0)
    {
        m_IsDead = true;
        m_Health = 0;
        m_MessageQueue->SendMessage("ObjectDead");
    }
    else if (m_Health > 0 and m_IsDead == true)
    {
        m_IsDead = false;
        m_MessageQueue->SendMessage("ObjectRevived");
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

Game::HealthComponent::HealthComponent(GameEngine::GameObject* owner, GameEngine::MessageQueue* messageQueue, unsigned int health, unsigned int maxHealth)
    : BaseComponent{owner}
    , m_IsDead{ false }
    , m_Health{ health }
    , m_MaxHealth{ maxHealth }
    , m_MessageQueue{ messageQueue }
{
    CheckHealth();
}

void Game::HealthComponent::TakeDamage()
{
    --m_Health;

    m_MessageQueue->SendMessage("ObjectDamageTaken");
    CheckHealth();
}

void Game::HealthComponent::Heal()
{
    ++m_Health;

    m_MessageQueue->SendMessage("ObjectHealed");
    CheckHealth();
}

int Game::HealthComponent::GetHealth() const
{
    return m_Health;
}

void Game::HealthComponent::SetMaxHealth(unsigned int newMaxHealth)
{
    m_MaxHealth = newMaxHealth;

    CheckHealth();
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
