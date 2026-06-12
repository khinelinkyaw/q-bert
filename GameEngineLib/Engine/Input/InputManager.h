#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Singleton.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
    class ControllerComponent;
    class InputManager final : public Singleton<InputManager>
    {
    private:
        KeyboardInputDevice m_KeyboardInputDevice{};
        std::vector<GamepadInputDevice> m_GamepadInputDevices{};
        NullInputDevice m_NullInputDevice{};
        std::unordered_map<std::string, std::unique_ptr<InputMapping>> m_InputMappingMap{};

    public:
        InputMapping* AddInputMapping(std::string const& name, std::unique_ptr<InputMapping>&& inputMapping);
        InputMapping* GetInputMapping(std::string const& name);

        KeyboardInputDevice& GetKeyboardInputDevice() { return m_KeyboardInputDevice; }
        GamepadInputDevice& GetGamepadInputDevice(int playerIndex);
        NullInputDevice& GetNullInputDevice() { return m_NullInputDevice; }

        bool ProcessInput();

        InputManager();
        ~InputManager() override = default;
    };
}

#endif