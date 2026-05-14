#include <Map/Graph.h>
#include <Characters/MovementState.h>

#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>

#include <cmath>
#include <memory>

using namespace Game;

void MovementState::SendEvent(MovementEvent event)
{
    m_EventQueue.push_back(event);
}

MovementState::MovementState(GameEngine::GameObject* gameObject)
    : m_pTransformComponent{ gameObject->GetTransform() }
    , m_pTextureComponent{ gameObject->GetComponent<GameEngine::TextureComponent>() }
{
}

std::unique_ptr<MovementState> HopState::Update(GameEngine::GameObject* gameObject)
{
    std::unique_ptr<MovementState> result{};
    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);
        result = std::make_unique<IdleState>(gameObject);
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
    //m_pTextureComponent->SetTexture(m_HopTexturePath);
    m_StartPos = m_pTransformComponent->GetLocalPosition();

    switch (m_HopDirection)
    {
    case MovementEvent::OnHoppedUp:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y, 0.f};
        break;
    case MovementEvent::OnHoppedDown:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y, 0.f };
        break;
    case MovementEvent::OnHoppedLeft:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y, 0.f };
        break;
    case MovementEvent::OnHoppedRight:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y, 0.f };
        break;
    }

    m_ElapsedTime = 0.f;
}

void HopState::OnExit()
{
    assert(m_pGraph != nullptr);

    m_pGraph->SendEvent(GraphEvent::QBertMoved, m_pTransformComponent->GetOwnerObject());
}

HopState::HopState(GameEngine::GameObject* gameObject, MovementEvent hopDirection)
    : MovementState{gameObject}
    , m_HopDirection{hopDirection}
{
}

std::unique_ptr<MovementState> IdleState::Update(GameEngine::GameObject* gameObject)
{
    if (!m_EventQueue.empty())
    {
        auto event{ m_EventQueue.front() };
        m_EventQueue.pop_front();

        switch (event)
        {
        case MovementEvent::OnHoppedUp:
            return std::make_unique<HopState>(gameObject, MovementEvent::OnHoppedUp);
        case MovementEvent::OnHoppedDown:
            return std::make_unique<HopState>(gameObject, MovementEvent::OnHoppedDown);
        case MovementEvent::OnHoppedLeft:
            return std::make_unique<HopState>(gameObject, MovementEvent::OnHoppedLeft);
        case MovementEvent::OnHoppedRight:
            return std::make_unique<HopState>(gameObject, MovementEvent::OnHoppedRight);
        }
    }

    return nullptr;
}

void IdleState::OnEnter()
{
    //m_pTextureComponent->SetTexture(m_IdleTexturePath);
}

IdleState::IdleState(GameEngine::GameObject* gameObject)
    :MovementState{ gameObject }
{
}
