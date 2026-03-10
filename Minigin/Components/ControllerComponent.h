#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include "BaseComponent.h"
#include "Command.h"
#include <glm/fwd.hpp>
#include <list>
#include <memory>
#include <type_traits>

namespace dae
{
    template<typename T> concept DerivedObjectCommand = std::is_base_of<ObjectCommand, T>::value;

    class ControllerComponent final : public BaseComponent
    {
    private:
        std::list<std::unique_ptr<ObjectCommand>> m_Commands{};
    public:
        //void AddCommand(std::unique_ptr<ObjectCommand> pObjectCommand);

        template<typename CommandType, typename... Args> requires DerivedObjectCommand<CommandType>
        void AddCommand(Args&& ... args);
        void ClearCommands();
        void ExecuteCommands();

        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const&) const override;

        ControllerComponent() = default;
        ~ControllerComponent() override = default;
        ControllerComponent(const ControllerComponent& other) = delete;
        ControllerComponent(ControllerComponent&& other) = delete;
        ControllerComponent& operator=(const ControllerComponent& other) = delete;
        ControllerComponent& operator=(ControllerComponent&& other) = delete;
    };

    template<typename CommandType, typename... Args> requires DerivedObjectCommand<CommandType>
    void ControllerComponent::AddCommand(Args && ...args)
    {
        m_Commands.push_back(std::make_unique<CommandType>(args...));
    }
}

#endif
