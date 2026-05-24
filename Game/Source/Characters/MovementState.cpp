#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Map/Graph.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Decoupling/Event.h>

#include <cmath>
#include <memory>

using namespace Game;

void Game::MovementState::RefreshSprite()
{
    m_pTransformComponent->GetOwner()->SendEvent<EventArgMove>("ChangeSprite", m_Event, m_Direction);
}

MovementState::MovementState(GameEngine::GameObject* gameObject, LookDirection direction, MovementEvent event)
    : m_pTransformComponent{ gameObject->GetTransform() }
    , m_Direction{ direction }
    , m_Event{ event }
{
}

std::unique_ptr<MovementState> IdleState::Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue)
{
    std::unique_ptr<MovementState> result{nullptr};

    if (!moveQueue.empty())
    {
        auto event{ moveQueue.front() };

        switch (event.first)
        {
        case MovementEvent::OnHop:
            result = std::make_unique<HopState>(gameObject, event.second);
            break;
        case MovementEvent::OnIdleWait:
            result = std::make_unique<IdleWaitState>(gameObject, event.second);
        }

        moveQueue.pop();
    }

    return result;
}

void IdleState::OnEnter()
{
    RefreshSprite();
    m_pTransformComponent->GetOwner()->SendEvent<GameEngine::EventArg>("IdleEnter");
}

IdleState::IdleState(GameEngine::GameObject* gameObject, LookDirection direction)
    : MovementState{ gameObject, direction, MovementEvent::OnIdle }
{
}

std::unique_ptr<MovementState> Game::IdleWaitState::Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue)
{
    m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();

    if (m_ElapsedTime > m_Duration)
    {
        return IdleState::Update(gameObject, moveQueue);
    }

    return nullptr;
}

Game::IdleWaitState::IdleWaitState(GameEngine::GameObject* gameObject, LookDirection direction)
    : IdleState{ gameObject, direction }
{
}

std::unique_ptr<MovementState> HopState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    std::unique_ptr<MovementState> result{};
    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);
        result = std::make_unique<IdleState>(gameObject, m_Direction);
    }
    else
    {
        float arcHeight{ HOP_HEIGHT * (4.0f * time * (1.f - time)) };
        float x{ std::lerp(m_StartPos.x, m_DestPos.x, time) };
        float y{ std::lerp(m_StartPos.y, m_DestPos.y, time) - arcHeight};

        m_pTransformComponent->SetLocalPosition({ x, y, 0.f });

        m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();
    }

    return result;
}

void HopState::OnEnter()
{
    m_StartPos = m_pTransformComponent->GetLocalPosition();

    switch (m_Direction)
    {
    case LookDirection::UpLeft:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y, 0.f};
        break;
    case LookDirection::DownRight:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y, 0.f };
        break;
    case LookDirection::DownLeft:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y, 0.f };
        break;
    case LookDirection::UpRight:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y, 0.f };
        break;
    }

    RefreshSprite();
    m_ElapsedTime = 0.f;

    GameEngine::ServiceLocator::Get().GetSoundSystem().Play(0);
}

void HopState::OnExit()
{
    assert(m_pGraph != nullptr);

    m_pGraph->SendEvent(GraphEvent::EntityMoved, m_pTransformComponent->GetOwner());
}

HopState::HopState(GameEngine::GameObject* gameObject, LookDirection direction)
    : MovementState{gameObject, direction, MovementEvent::OnHop}
{
}

std::unique_ptr<MovementState> Game::FallingState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    std::unique_ptr<MovementState> result{ nullptr };

    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);
        result = std::make_unique<IdleState>(gameObject, m_Direction);
    }
    else
    {
        float y{ std::lerp(m_StartPos.y, m_DestPos.y, time) };
        m_pTransformComponent->SetLocalPosition({ m_StartPos.x, y, 0.f });
        m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();
    }

    return result;
}

Game::FallingState::FallingState(GameEngine::GameObject* gameObject, LookDirection direction)
    : MovementState{ gameObject, direction, MovementEvent::OnFalling }
{
    m_DestPos = m_pTransformComponent->GetLocalPosition();
    m_StartPos = { m_DestPos.x, m_DestPos.y - FALL_HEIGHT, 0.f };
}
