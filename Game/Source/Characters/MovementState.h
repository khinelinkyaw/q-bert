#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <Map/Block.h>

#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>

namespace Game
{
    enum class LookDirection
    {
        UpRight = 0,
        UpLeft = 1,
        DownRight = 2,
        DownLeft = 3,
    };

    enum class MovementEvent
    {
        OnIdle = 00,
        OnIdleWait = 00,
        OnHop = 10,
        OnDeath = 20,
        OnVictory = 30,
    };

    using MoveQueue = std::queue<std::pair<MovementEvent, LookDirection>>;

    inline int GetSpriteIndexFromMap(std::unordered_map<int, int> const& spriteIndexMap, LookDirection direction, MovementEvent movementEvent)
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
        GameEngine::TransformComponent* m_pTransformComponent{};
        LookDirection m_Direction{};
        MovementEvent m_Event{};

    public:
        virtual std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) = 0;
        virtual void OnEnter();
        virtual void OnExit() = 0;

        void RefreshSprite() { RefreshSprite(m_Event, m_Direction); }
        void RefreshSprite(MovementEvent event, LookDirection direction);

        MovementState(GameEngine::GameObject* gameObject, LookDirection direction, MovementEvent event);
        virtual ~MovementState() = default;
    };

    class IdleState : public MovementState
    {
    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override;
        virtual void OnExit() override {};

        IdleState(GameEngine::GameObject* gameObject, LookDirection direction);
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

        IdleWaitState(GameEngine::GameObject* gameObject, LookDirection direction);
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
        std::string m_HopTexturePath{};
        vec3 m_StartPos{};
        vec3 m_DestPos{};

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        void OnEnter() override;
        void OnExit() override;

        HopState(GameEngine::GameObject* gameObject, LookDirection direction);
        ~HopState() override = default;
    };

    class FallingState final : public MovementState
    {
    private:
        static float constexpr FALL_HEIGHT{ 300.f };
        static float constexpr DURATION{ 1.f };

        float m_ElapsedTime{};
        vec3 m_StartPos{};
        vec3 m_DestPos{};
    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject, MoveQueue& moveQueue) override;
        //void OnEnter() override;
        void OnExit() override {};

        FallingState(GameEngine::GameObject* gameObject, LookDirection direction);
        ~FallingState() override = default;
    };
}

#endif
