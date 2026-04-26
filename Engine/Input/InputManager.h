#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Engine/Input/InputDevice.h>
#include <Engine/Misc/Singleton.h>
#include <vector>

namespace GameEngine
{
    class ControllerComponent;
    class InputManager final : public Singleton<InputManager>
    {
    private:
        KeyboardInputDevice m_KeyboardInputDevice{};
        std::vector<GamepadInputDevice> m_GamepadInputDevices{};
        GamepadInputDevice m_NullGamepadInputDevice{};

    public:
        KeyboardInputDevice& GetKeyboardInputDevice() { return m_KeyboardInputDevice; }
        GamepadInputDevice& GetGamepadInputDevice(int playerIndex);

        bool ProcessInput();

        InputManager() = default;
        ~InputManager() override = default;
    };
}

#endif