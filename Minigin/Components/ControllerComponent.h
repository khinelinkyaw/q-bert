#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include "BaseComponent.h"
#include "Command.h"
#include <glm/fwd.hpp>
#include <list>
#include <memory>

namespace dae
{
    class ControllerComponent final : public BaseComponent
    {
    private:
        std::list<std::unique_ptr<Command>> m_Commands{};
    public:
        void AddCommand(std::unique_ptr<Command> pCommand);
        void ClearCommands();
        void ExecuteCommands();

        void FixedUpdate() override;
        void Update(float) override;
        void Render(glm::vec3 const&) const override;

        ControllerComponent() = default;
        ~ControllerComponent() override = default;
        ControllerComponent(const ControllerComponent& other) = delete;
        ControllerComponent(ControllerComponent&& other) = delete;
        ControllerComponent& operator=(const ControllerComponent& other) = delete;
        ControllerComponent& operator=(ControllerComponent&& other) = delete;
    };
}

#endif
