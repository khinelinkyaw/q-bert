#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "InputDevice.h"
#include "Singleton.h"
#include <vector>

namespace GameEngine
{
    class ControllerComponent;
    class InputManager final : public Singleton<InputManager>
    {
    private:
        std::vector<ControllerInfo> m_PlayerControllers{};

    public:
        void RegisterController(ControllerComponent* controller, InputDeviceType inputType = InputDeviceType::Keyboard);
        bool ProcessInput();
    };
}

#endif