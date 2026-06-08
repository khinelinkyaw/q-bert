#include <Characters/MovementState.h>
#include <Components/BaseCreature.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>
#include <Map/Block.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/Time.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Events/EventArg.h>

#include <cmath>
#include <memory>

using namespace Game;

//void Game::MovementState::OnEnter()
//{   
//    RefreshSprite();
//}

//void Game::MovementState::RefreshSprite(MovementEvent event, Direction direction)
//{
//    m_pOwner->SendEvent<EventArgMove>("ChangeSprite", event, direction);
//}

MovementState::MovementState(GameEngine::GameObject* gameObject, Direction direction, MovementEvent event)
    : m_pOwner{ gameObject }
    , m_pTransformComponent{ gameObject->GetTransform() }
    , m_Direction{ direction }
    , m_Event{ event }
{
}

std::unique_ptr<MovementState> IdleState::Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue)
{
    std::unique_ptr<MovementState> result{nullptr};

    if (!moveQueue.empty())
    {
        auto& instruction{ moveQueue.front() };

        switch (instruction.MovementEvent)
        {
        case MovementEvent::OnHop:
            result = std::make_unique<HopState>(gameObject, instruction.Direction);
            break;
        case MovementEvent::OnIdleWait:
            result = std::make_unique<IdleWaitState>(gameObject, instruction.Direction);
        }

        moveQueue.pop();
    }

    return result;
}

void IdleState::OnEnter()
{
    m_pOwner->SendEvent<GameEngine::EventArg>("IdleEnter");
    //MovementState::OnEnter();
}

IdleState::IdleState(GameEngine::GameObject* gameObject, Direction direction)
    : MovementState{ gameObject, direction, MovementEvent::OnIdle}
{
}

std::unique_ptr<MovementState> Game::IdleWaitState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime > m_Duration)
    {
        return std::make_unique<IdleState>(gameObject, m_Direction);
    }

    return nullptr;
}

void Game::IdleWaitState::OnExit()
{
    m_pOwner->SendEvent<GameEngine::EventArg>("IdleWaitExit");
}

Game::IdleWaitState::IdleWaitState(GameEngine::GameObject* gameObject, Direction direction)
    : IdleState{ gameObject, direction }
{
}

std::unique_ptr<MovementState> HopState::Update(GameEngine::GameObject* gameObject, MoveQueue&)
{
    float time{ m_ElapsedTime / DURATION };

    if (time > 1.0f)
    {
        m_pTransformComponent->SetLocalPosition(m_DestPos);

        auto graph{ GameEngine::SceneManager::Get().GetObjectByName("Graph")->GetComponent<Graph>() };
        graph->SendGraphEvent(GraphEvent::EntityMoved, gameObject->GetId());
        auto destinationBlock{ graph->GetBlock(m_DestPos.x, m_DestPos.y) };

        if (destinationBlock == nullptr)
        {
            return std::make_unique<DyingState>(gameObject, m_Direction);
        }
        else
        {
            return std::make_unique<IdleState>(gameObject, m_Direction);
        }
    }
    else
    {
        float arcHeight{ HOP_HEIGHT * (4.0f * time * (1.f - time)) };
        float x{ std::lerp(m_StartPos.x, m_DestPos.x, time) };
        float y{ std::lerp(m_StartPos.y, m_DestPos.y, time) - arcHeight};

        m_pTransformComponent->SetLocalPosition({ x, y });

        m_ElapsedTime += GameEngine::GetDeltaTime();
    }

    return nullptr;
}

void HopState::OnEnter()
{
    m_StartPos = m_pTransformComponent->GetWorldPosition();

    switch (m_Direction)
    {
    case Direction::UpLeft:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y};
        break;
    case Direction::DownRight:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y};
        break;
    case Direction::DownLeft:
        m_DestPos = { m_StartPos.x - HOP_RANGE_X, m_StartPos.y + HOP_RANGE_Y};
        break;
    case Direction::UpRight:
        m_DestPos = { m_StartPos.x + HOP_RANGE_X, m_StartPos.y - HOP_RANGE_Y };
        break;
    case Direction::LevelLeft: 
        m_DestPos = { m_StartPos.x - Block::BLOCK_SIZE, m_StartPos.y };
        break;
    case Direction::LevelRight:
        m_DestPos = { m_StartPos.x + Block::BLOCK_SIZE, m_StartPos.y };
        break;
    }

    m_ElapsedTime = 0.f;
    GameEngine::ServiceLocator::Get().GetSoundSystem().Play(0);
    // MovementState::OnEnter();
}

void HopState::OnExit()
{
    m_pOwner->SendEvent<GameEngine::EventArg>("HopExit");
}

HopState::HopState(GameEngine::GameObject* gameObject, Direction direction)
    : MovementState{ gameObject, direction, MovementEvent::OnHop }
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
        m_pTransformComponent->SetLocalPosition({ m_StartPos.x, y});
        m_ElapsedTime += GameEngine::GetDeltaTime();
    }

    return result;
}

Game::FallingState::FallingState(GameEngine::GameObject* gameObject, Direction direction)
    : MovementState{ gameObject, direction, MovementEvent::OnHop }
{
    m_DestPos = m_pTransformComponent->GetLocalPosition();
    m_StartPos = { m_DestPos.x, m_DestPos.y - FALL_HEIGHT };
}

std::unique_ptr<MovementState> Game::DyingState::Update(GameEngine::GameObject* gameObject, MoveQueue& )
{
    // Make it unique per creature type later if we want different death animations
    return std::make_unique<IdleState>(gameObject, m_Direction );
}

void Game::DyingState::OnExit()
{
}

Game::DyingState::DyingState(GameEngine::GameObject* gameObject, Direction direction)
    : MovementState{ gameObject, direction, MovementEvent::OnDeath }
    , m_pBreed{ gameObject->GetComponent<BaseCreature>()->GetBreed() }
{
}
