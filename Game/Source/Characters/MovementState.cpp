#include <Characters/MovementState.h>

#include <Engine/Core/Minigin.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>

#include <cmath>
#include <memory>

using namespace Game;

void Game::MovementState::SendEvent(MovementEvent event)
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
    float time{ m_ElapsedTime / DURATION };

    if (time > 1.f)
    {
        return std::make_unique<IdleState>(gameObject);
    }

    auto currentPos{ m_pTransformComponent->GetLocalPosition() };

    float x{ std::lerp(currentPos.x, m_Destination.x, time) };
    float y{ std::lerp(currentPos.y, m_Destination.y, time) - MAX_HEIGHT * (4.0f * time * (1.0f - time)) };

    m_pTransformComponent->SetLocalPosition({ x,y,0.f });

    m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();

    return nullptr;
}

void HopState::OnEnter()
{
    m_pTextureComponent->SetTexture(m_HopTexturePath);
    m_ElapsedTime = 0.f;

    auto currentPosition{ m_pTransformComponent->GetLocalPosition() };

    switch (m_HopDirection)
    {
    case MovementEvent::OnHoppedUp:
        m_Destination = { currentPosition.x, currentPosition.y - HOP_RANGE, 0.f };
        break;
    case MovementEvent::OnHoppedDown:
        m_Destination = { currentPosition.x, currentPosition.y + HOP_RANGE, 0.f };
        break;
    case MovementEvent::OnHoppedLeft:
        m_Destination = { currentPosition.x - HOP_RANGE, currentPosition.y, 0.f };
        break;
    case MovementEvent::OnHoppedRight:
        m_Destination = { currentPosition.x + HOP_RANGE, currentPosition.y, 0.f };
        break;
    }
}

HopState::HopState(GameEngine::GameObject* gameObject, MovementEvent hopDirection)
    : MovementState{gameObject}
    , m_HopDirection{hopDirection}
{
}

std::unique_ptr<MovementState> Game::IdleState::Update(GameEngine::GameObject* gameObject)
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
    m_pTextureComponent->SetTexture(m_IdleTexturePath);
}

IdleState::IdleState(GameEngine::GameObject* gameObject)
    :MovementState{ gameObject }
{
}
