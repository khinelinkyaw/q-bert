#ifndef COMMAND_QUEUE_COMPONENT_H
#define COMMAND_QUEUE_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Core/GameObject.h>

#include <memory>
#include <queue>
#include <utility>

namespace GameEngine
{
    class CommandQueueComponent final : public BaseComponent
    {
    private:
        std::queue<std::unique_ptr<Command>> m_CommandQueue{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vector3 const&) const override {};

        template<typename CommandType, typename... Args> requires DerivedCommandClass<CommandType>
        void AddCommand(Args&& ... args);
        void ClearCommands();
        void HandleCommands();

        CommandQueueComponent(GameObject* owner);
        ~CommandQueueComponent() override = default;
    };

    template<typename CommandType, typename ...Args> requires DerivedCommandClass<CommandType>
    inline void CommandQueueComponent::AddCommand(Args && ...args)
    {
        m_CommandQueue.push(std::make_unique<CommandType>(std::forward<Args>(args)...));
    }
}

#endif