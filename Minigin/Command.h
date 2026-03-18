#ifndef COMMAND_H
#define COMMAND_H

#include "./Modules/GameObject.h"
#include "./Modules/Transform.h"

namespace GameEngine
{
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
        Transform m_Movement{};
    public:
        void SetMovement(const Transform& movement) { m_Movement = movement; }
        void Execute(GameObject& gameObject) override;

        MoveCommand(float x = 0.f, float y = 0.f);
    };
}

#endif