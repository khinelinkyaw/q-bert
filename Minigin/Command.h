#ifndef COMMAND_H
#define COMMAND_H

#include "./Modules/GameObject.h"
#include "./Modules/Transform.h"

namespace dae
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
        virtual void Execute() = 0;
    };

    class ObjectCommand : public Command
    {
    protected:
        GameObject* m_pObject{ nullptr };
    public:
        void SetObject(GameObject* pObject) { m_pObject = pObject; }
    };

    class MoveCommand final : public ObjectCommand
    {
        Transform m_Movement{};
    public:
        void SetMovement(const Transform& movement) { m_Movement = movement; }
        void Execute() override;

        MoveCommand(float x = 0.f, float y = 0.f);
    };
}

#endif