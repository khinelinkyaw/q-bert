#ifndef COMMAND_H
#define COMMAND_H

#include <Engine/Core/GameObject.h>

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
}

#endif