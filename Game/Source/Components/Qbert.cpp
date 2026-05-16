#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Observer.h>

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/Qbert.h>

#include <memory>
#include <string>
#include <utility>

void Game::QBert::CheckHealth()
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

void Game::QBert::Update()
{
    auto newState = m_pMovementState->Update(GetOwner());

    if (newState)
    {
        m_pMovementState->OnExit();
        m_pMovementState = std::move(newState);
        m_pMovementState->OnEnter();
    }
}

Game::QBert::QBert(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pMovementState{ std::make_unique<IdleState>(owner, FacingDir::DownRight) }
{
    CheckHealth();
}

void Game::QBert::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnMove")
    {
        auto movementEventArg{ static_cast<EventArgMove*>(eventArg) };

        m_pMovementState->SendEvent(movementEventArg->MovementEvent, movementEventArg->Direction);
    }
}

void Game::QBert::TakeDamage()
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

void Game::QBert::Heal()
{
    ++m_Health;

    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }

    NotifyObservers("UpdateHealth");
}

int Game::QBert::GetHealth() const
{
    return m_Health;
}

void Game::QBert::SetMaxHealth(int newMaxHealth)
{
    m_MaxHealth = newMaxHealth;

    CheckHealth();
}

void Game::QBert::Revive(int newHealth)
{
    m_Health = newHealth;

    CheckHealth();
}

void Game::QBert::Revive()
{
    Revive(m_MaxHealth);
}

bool Game::QBert::IsDead() const
{
    return m_IsDead;
}

void Game::QBert::SetName(std::string const& name)
{
    m_Name = name;
}

std::string Game::QBert::GetName() const
{
    return m_Name;
}

int Game::QBert::GetScore() const
{
    return m_Score;
}

void Game::QBert::IncrementScore(int increment)
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

void Game::QBert::AddObserver(GameEngine::Observer* pObserver)
{
    m_pObservers.push_back(pObserver);
}

void Game::QBert::NotifyObservers(std::string eventId)
{
    for (auto pObserver : m_pObservers)
    {
        pObserver->OnNotify(*GetOwner(), eventId);
    }
}

void Game::QBert::Init(int health, int maxHealth)
{
    m_Health = health;
    m_MaxHealth = maxHealth;

    NotifyObservers("UpdateHealth");
}
