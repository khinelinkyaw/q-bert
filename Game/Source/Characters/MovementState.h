#ifndef MOVEMENT_STATE_H
#define MOVEMENT_STATE_H

#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <Map/Block.h>
#include <Misc/Enums.h>
#include <Misc/Structs.h>
#include <Characters/Breed.h>

#include <memory>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Game
{
    using MoveQueue = std::queue<MoveInstruction>;

    inline int GetSpriteIndexFromMap(std::unordered_map<int, int> const& spriteIndexMap, Direction direction, MovementEvent movementEvent)
    {
        auto iter{ spriteIndexMap.find(static_cast<int>(direction) + static_cast<int>(movementEvent)) };

        if (iter != spriteIndexMap.end())
        {
            return iter->second;
        }
        else
        {
            return 0;
        }
    }
    
    class MovementState
    {
    protected:
        GameEngine::GameObject* m_pOwner{};
        GameEngine::TransformComponent* m_pTransformComponent{};
        Direction m_Direction{};
        MovementEvent m_Event{};

    public:
        virtual std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) = 0;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;

        // void RefreshSprite() { RefreshSprite(m_Event, m_Direction); }
        // void RefreshSprite(MovementEvent event, Direction direction);

        Direction GetDirection() const { return m_Direction; }
        MovementEvent GetMovementEvent() const { return m_Event; }

        MovementState(GameEngine::GameObject* gameObject, Direction direction, MovementEvent event);
        virtual ~MovementState() = default;
    };

    template<typename T> concept DerivedMovementState = std::is_base_of<MovementState, T>::value;

    class IdleState : public MovementState
    {
    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override;
        virtual void OnExit() override {};

        IdleState(GameEngine::GameObject* gameObject, Direction direction);
        ~IdleState() override = default;
    };

    class IdleWaitState final : public IdleState
    {
    private:
        float m_ElapsedTime{};
        float m_Duration{ 0.5f };

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnExit() override;

        IdleWaitState(GameEngine::GameObject* gameObject, Direction direction);
        ~IdleWaitState() override = default;
    };

    class HopState final : public MovementState
    {
    private:
        static float constexpr DURATION{ 0.35f };
        static float constexpr HOP_HEIGHT{ 10.f };
        static float constexpr HOP_RANGE_X{ Block::BLOCK_SIZE / 2.f };
        static float constexpr HOP_RANGE_Y{ Block::BLOCK_SIZE * 0.75f };

        float m_ElapsedTime{};
        vec2 m_StartPos{};
        vec2 m_DestPos{};

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override;
        void OnExit() override;

        HopState(GameEngine::GameObject* gameObject, Direction direction);
        ~HopState() override = default;
    };

    class FallingState final : public MovementState
    {
    private:
        static float constexpr FALL_HEIGHT{ 300.f };
        static float constexpr DURATION{ 1.f };

        float m_ElapsedTime{};
        vec2 m_StartPos{};
        vec2 m_DestPos{};
    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override {};
        void OnExit() override {};

        FallingState(GameEngine::GameObject* gameObject, Direction direction);
        ~FallingState() override = default;
    };

    class DyingState final : public MovementState
    {
    private:
        Breed* m_pBreed{};
    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override {};
        void OnExit() override;

        DyingState(GameEngine::GameObject* gameObject, Direction direction);
        ~DyingState() override = default;
    };
}

#endif
