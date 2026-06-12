#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Input/InputMapping.h>

#include <glm/fwd.hpp>

namespace Game
{
    class ControllerComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::InputMapping* m_pInputMapping{};
        GameEngine::InputDevice* m_pInputDevice{};

    public:
        void ProcessInput();

        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};

        void Init(GameEngine::InputMapping* pInputMapping, GameEngine::InputDevice* pInputDevice);
        ControllerComponent(GameEngine::GameObject* owner);
        ~ControllerComponent() override = default;
        ControllerComponent(const ControllerComponent& other) = delete;
        ControllerComponent(ControllerComponent&& other) = delete;
        ControllerComponent& operator=(const ControllerComponent& other) = delete;
        ControllerComponent& operator=(ControllerComponent&& other) = delete;
    };
}

#endif
