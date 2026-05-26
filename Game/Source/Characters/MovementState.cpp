#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Decoupling/Event.h>

#include <cmath>
#include <memory>

using namespace Game;

void Game::MovementState::OnEnter()
{   
    RefreshSprite();
}

void Game::MovementState::RefreshSprite(MovementEvent event, Direction direction)
{
    m_pTransformComponent->GetOwner()->SendEvent<EventArgMove>("ChangeSprite", event, direction);
}

MovementState::MovementState(GameEngine::GameObject* gameObject, Direction direction, MovementEvent event, BlockSurface surface)
    : m_pTransformComponent{ gameObject->GetTransform() }
    , m_Direction{ direction }
    , m_Surface{ surface }
    , m_Event{ event }
{
}

std::unique_ptr<MovementState> IdleState::Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue)
{
    std::unique_ptr<MovementState> result{nullptr};

    if (!moveQueue.empty())
    {
        auto instruction{ moveQueue.front() };

        switch (instruction.MovementEvent)
        {
        case MovementEvent::OnHop:
            result = std::make_unique<HopState>(gameObject, instruction.Direction, instruction.Surface);
            break;
        case MovementEvent::OnIdleWait:
            result = std::make_unique<IdleWaitState>(gameObject, instruction.Direction, instruction.Surface);
        }

        moveQueue.pop();
    }

    return result;
}

void IdleState::OnEnter()
{
    m_pTransformComponent->GetOwner()->SendEvent<GameEngine::EventArg>("IdleEnter");
    MovementState::OnEnter();
}

IdleState::IdleState(GameEngine::GameObject* gameObject, Direction direction, BlockSurface surface)
    : MovementState{ gameObject, direction, MovementEvent::OnIdle, surface }
{
}

std::unique_ptr<MovementState> Game::IdleWaitState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();

    if (m_ElapsedTime > m_Duration)
    {
        return std::make_unique<IdleState>(gameObject, m_Direction, m_Surface);
    }

    return nullptr;
}

void Game::IdleWaitState::OnExit()
{
    m_pTransformComponent->GetOwner()->SendEvent<GameEngine::EventArg>("IdleWaitExit");
}

Game::IdleWaitState::IdleWaitState(GameEngine::GameObject* gameObject, Direction direction, BlockSurface surface)
    : IdleState{ gameObject, direction, surface }
{
}

std::unique_ptr<MovementState> HopState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    std::unique_ptr<MovementState> result{};
    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);
        result = std::make_unique<IdleState>(gameObject, m_Direction, m_Surface);
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
    m_StartPos = m_pTransformComponent->GetWorldPosition();

    auto graph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() };
    auto currentBlock{ graph->GetBlock(m_StartPos.x, m_StartPos.y, m_Surface) };

    auto destBlock{ graph->GetBlockInDirection(*currentBlock, m_Direction) };

    if (destBlock == nullptr)
    {
        m_DestPos = m_StartPos;
    }
    else
    {
        m_DestPos = graph->GetBlockSurfaceCenter(*destBlock, m_Surface);
    }

    m_ElapsedTime = 0.f;
    GameEngine::ServiceLocator::Get().GetSoundSystem().Play(0);
    MovementState::OnEnter();
}

void HopState::OnExit()
{
    m_pTransformComponent->GetOwner()->SendEvent<GameEngine::EventArg>("HopExit");
}

HopState::HopState(GameEngine::GameObject* gameObject, Direction direction, BlockSurface surface)
    : MovementState{gameObject, direction, MovementEvent::OnHop, surface}
{
}

std::unique_ptr<MovementState> Game::FallingState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    std::unique_ptr<MovementState> result{ nullptr };

    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);
        result = std::make_unique<IdleState>(gameObject, m_Direction, m_Surface);
    }
    else
    {
        float y{ std::lerp(m_StartPos.y, m_DestPos.y, time) };
        m_pTransformComponent->SetLocalPosition({ m_StartPos.x, y, 0.f });
        m_ElapsedTime += GameEngine::Minigin::GetDeltaTime();
    }

    return result;
}

Game::FallingState::FallingState(GameEngine::GameObject* gameObject, Direction direction, BlockSurface surface)
    : MovementState{ gameObject, direction, MovementEvent::OnHop, surface }
{
    m_DestPos = m_pTransformComponent->GetLocalPosition();
    m_StartPos = { m_DestPos.x, m_DestPos.y - FALL_HEIGHT, 0.f };
}
