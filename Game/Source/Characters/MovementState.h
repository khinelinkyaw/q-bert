#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include <Engine/Components/TextureComponent.h>
#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>

#include <list>
#include <memory>
#include <string>

namespace Game
{
    enum class MovementEvent
    {
        OnHoppedUp,
        OnHoppedDown,
        OnHoppedLeft,
        OnHoppedRight,
        OnIdle,
        OnDeath,
        OnVictory
    };
    
    class MovementState
    {
    protected:
        GameEngine::TransformComponent* m_pTransformComponent{};
        GameEngine::TextureComponent* m_pTextureComponent{};
        std::list<MovementEvent> m_EventQueue{};

    public:
        virtual std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) = 0;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;
        void SendEvent(MovementEvent event);

        MovementState(GameEngine::GameObject* gameObject);
        virtual ~MovementState() = default;
    };

    class HopState final : public MovementState
    {
    private:
        static float constexpr MAX_HEIGHT{ 10.f };
        static float constexpr DURATION{ 2.f };
        static float constexpr HOP_RANGE{ 50.f };
        MovementEvent m_HopDirection{};
        float m_ElapsedTime{};
        std::string m_HopTexturePath{};
        glm::vec3 m_Destination{};

    public:
        std::unique_ptr<MovementState> Update(GameEngine::GameObject* gameObject) override;
        void OnEnter() override;
        void OnExit() override {};

        HopState(GameEngine::GameObject* gameObject, MovementEvent hopDirection);
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

        IdleState(GameEngine::GameObject* gameObject);
        ~IdleState() override = default;
    };
}

#endif
