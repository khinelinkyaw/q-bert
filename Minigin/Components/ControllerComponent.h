#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include "BaseComponent.h"
#include "Command.h"
#include <glm/fwd.hpp>
#include <list>
#include <memory>
#include <type_traits>
#include <utility>

namespace GameEngine
{
    template<typename T> concept DerivedCommandClass = std::is_base_of<Command, T>::value;

    class InputDevice;
    class ControllerComponent final : public BaseComponent
    {
    private:
        std::list<std::unique_ptr<Command>> m_Commands{};
        float m_Speed{};

        template<typename CommandType, typename... Args> requires DerivedCommandClass<CommandType>
        void AddCommand(Args&& ... args);
        void ClearCommands();
        void ExecuteCommands();
    public:

        void SetSpeed(float speed) { m_Speed = speed; }
        float GetSpeed() const { return m_Speed; }
        void ProcessInput(InputDevice& inputDevice);

        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const&) const override;

        ControllerComponent(float speed = 1.f);
        ~ControllerComponent() override = default;
        ControllerComponent(const ControllerComponent& other) = delete;
        ControllerComponent(ControllerComponent&& other) = delete;
        ControllerComponent& operator=(const ControllerComponent& other) = delete;
        ControllerComponent& operator=(ControllerComponent&& other) = delete;
    };

    template<typename CommandType, typename... Args> requires DerivedCommandClass<CommandType>
    void ControllerComponent::AddCommand(Args && ...args)
    {
        m_Commands.push_back(std::make_unique<CommandType>(std::forward<Args>(args)...));
    }
}

#endif
