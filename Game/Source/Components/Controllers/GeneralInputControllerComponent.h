#ifndef GENERAL_INPUT_CONTROLLER_COMPONENT_H
#define GENERAL_INPUT_CONTROLLER_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Types.h>

#include <vector>

namespace Game
{
    class GeneralInputController final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::InputMapping* m_pInputMapping{
        
        };
        std::vector<GameEngine::InputDevice*> m_InputDevices{};

    public:
        void ProcessInput(GameEngine::InputDevice const& inputDevice);

        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};

        void AddInputDevice(GameEngine::InputDevice* inputDevice);
        void SetInputMapping(GameEngine::InputMapping* pInputMapping) { m_pInputMapping = pInputMapping; }
        GeneralInputController(GameEngine::GameObject* owner);
        ~GeneralInputController() override = default;
    };
}

#endif
