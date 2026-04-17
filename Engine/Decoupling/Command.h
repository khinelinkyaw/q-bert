#ifndef COMMAND_H
#define COMMAND_H

#include <Engine/Misc/GameObject.h>
#include <Engine/Misc/Transform.h>

namespace GameEngine
{
    using vector3 = glm::vec3;

    enum class CommandState
    {
        Initial,
        Success,
        Failed,
        Cancelled
    };

    class Command
    {
    protected:
        CommandState m_State{ CommandState::Initial };
    public:
        virtual void Execute(GameObject& gameObject) = 0;
        virtual ~Command() = default;
    };

    class MoveCommand final : public Command
    {
        vector3 m_Movement{};
    public:
        void SetMovement(vector3 const& movement) { m_Movement = movement; }
        void Execute(GameObject& gameObject) override;

        MoveCommand(float x = 0.f, float y = 0.f);
    };

    class TakeDamageCommand final : public Command
    {
    public:
        void Execute(GameObject& gameObject) override;
    };

    class IncreaseScore final : public Command
    {
    public:
        void Execute(GameObject& gameObject) override;
    };
}

#endif