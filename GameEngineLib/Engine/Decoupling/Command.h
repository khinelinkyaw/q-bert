#ifndef COMMAND_H
#define COMMAND_H

#include <Engine/Core/GameObject.h>

#include <type_traits>

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

    template<typename T> concept DerivedCommandClass = std::is_base_of<Command, T>::value;
}

#endif