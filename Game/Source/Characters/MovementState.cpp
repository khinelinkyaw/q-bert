#include <Map/Graph.h>
#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/ServiceLocator.h>

#include <cmath>
#include <memory>

using namespace Game;

void MovementState::SendEvent(MovementEvent event, LookDirection direction)
{
    m_EventQueue.push({ event, direction });
}

void Game::MovementState::RefreshSprite()
{
    m_pTransformComponent->GetOwner()->SendEvent<EventArgMove>("ChangeSprite", m_Event, m_Direction);
}

MovementState::MovementState(GameEngine::GameObject* gameObject, LookDirection direction)
    : m_pTransformComponent{ gameObject->GetTransform() }
    , m_Direction{ direction }
{
}

std::unique_ptr<MovementState> HopState::Update(GameEngine::GameObject* gameObject)
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
    : MovementState{gameObject, direction}
{
    m_Event = MovementEvent::OnHop;
}

std::unique_ptr<MovementState> IdleState::Update(GameEngine::GameObject* gameObject)
{
    if (!m_EventQueue.empty())
    {
        auto event{ m_EventQueue.front() };

        switch (event.first)
        {
        case MovementEvent::OnHop:
            return std::make_unique<HopState>(gameObject, event.second);
        }

        m_EventQueue.pop();
    }

    return nullptr;
}

void IdleState::OnEnter()
{
    RefreshSprite();
}

IdleState::IdleState(GameEngine::GameObject* gameObject, LookDirection direction)
    : MovementState{ gameObject, direction }
{
    m_Event = MovementEvent::OnIdle;
}
