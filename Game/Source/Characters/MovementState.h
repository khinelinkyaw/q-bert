#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include <Engine/Animation/Animation.h>
#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>

#include <Map/Block.h>
#include <Map/Graph.h>

#include <memory>
#include <queue>
#include <string>
#include <utility>

namespace Game
{
    enum class FacingDir
    {
        UpRight = 0,
        UpLeft = 2,
        DownRight = 4,
        DownLeft = 6
    };

    enum class MovementEvent
    {
        OnIdle = 0,
        OnHop = 1,
        OnDeath,
        OnVictory
    };
    
    class MovementState
    {
    protected:
        static Graph* m_pGraph;

        GameEngine::TransformComponent* m_pTransformComponent{};
        GameEngine::SpriteComponent* m_pTextureComponent{};
        std::queue<std::pair<MovementEvent, FacingDir>> m_EventQueue{};
        FacingDir m_CurrentDirection{ FacingDir::UpRight };

    public:
        virtual std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) = 0;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;
        void SendEvent(MovementEvent event, FacingDir direction);

        static void SetGraph(Graph* graph) { m_pGraph = graph; }

        MovementState(GameEngine::GameObject* gameObject, FacingDir direction);
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

        HopState(GameEngine::GameObject* gameObject, FacingDir direction);
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

        IdleState(GameEngine::GameObject* gameObject, FacingDir direction);
        ~IdleState() override = default;
    };
}

#endif
