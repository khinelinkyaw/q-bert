#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>

#include <Map/Block.h>
#include <Map/Graph.h>

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
        DownLeft = 3
    };

    enum class MovementEvent
    {
        OnIdle = 00,
        OnHop = 10,
        OnDeath = 20,
        OnVictory = 30
    };

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
        static Graph* m_pGraph;

        GameEngine::TransformComponent* m_pTransformComponent{};
        std::queue<std::pair<MovementEvent, LookDirection>> m_EventQueue{};
        LookDirection m_Direction{ LookDirection::UpRight };
        MovementEvent m_Event{ MovementEvent::OnIdle };

    public:
        virtual std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) = 0;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;
        void SendEvent(MovementEvent event, LookDirection direction);

        void RefreshSprite();

        static void SetGraph(Graph* graph) { m_pGraph = graph; }

        MovementState(GameEngine::GameObject* gameObject, LookDirection direction);
        virtual ~MovementState() = default;
    };
    inline Graph* MovementState::m_pGraph = nullptr;

    class HopState final : public MovementState
    {
    private:
        static float constexpr DURATION{ 0.35f };
        static float constexpr HOP_HEIGHT{ 10.f };
        static float constexpr HOP_RANGE_X{ Block::BLOCK_SIZE / 2.f };
        static float constexpr HOP_RANGE_Y{ Block::BLOCK_SIZE * 0.75f };

        float m_ElapsedTime{};
        std::string m_HopTexturePath{};
        glm::vec3 m_StartPos{};
        glm::vec3 m_DestPos{};

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) override;
        void OnEnter() override;
        void OnExit() override;

        HopState(GameEngine::GameObject* gameObject, LookDirection direction);
        ~HopState() override = default;
    };

    class IdleState final : public MovementState
    {
    private:
        std::string m_IdleTexturePath{};

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) override;
        void OnEnter() override;
        void OnExit() override {};

        IdleState(GameEngine::GameObject* gameObject, LookDirection direction);
        ~IdleState() override = default;
    };
}

#endif
