#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/GameObject.h>

#include <glm/fwd.hpp>
#include <list>
#include <memory>
#include <type_traits>
#include <utility>

namespace Game
{
    template<typename T> concept DerivedCommandClass = std::is_base_of<GameEngine::Command, T>::value;

    class GameEngine::InputDevice;
    class ControllerComponent final : public GameEngine::BaseComponent
    {
    private:
        static float constexpr DEFAULT_SPEED{ 100.f };

        GameEngine::InputMapping* m_pInputMapping{};
        GameEngine::InputDevice* m_pInputDevice{};

        std::list<std::unique_ptr<GameEngine::Command>> m_Commands{};
        float m_Speed{ DEFAULT_SPEED };

        template<typename CommandType, typename... Args> requires DerivedCommandClass<CommandType>
        void AddCommand(Args&& ... args);
        void ClearCommands();
        void ExecuteCommands();

    public:
        void ProcessInput();

        void SetSpeed(float speed) { m_Speed = speed; }
        float GetSpeed() const { return m_Speed; }

        void FixedUpdate() override;
        void Update() override {};
        void Render(glm::vec3 const&) const override {};

        void Init(GameEngine::InputMapping* pInputMapping, GameEngine::InputDevice* pInputDevice, float speed = DEFAULT_SPEED);
        ControllerComponent(GameEngine::GameObject* owner);
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
