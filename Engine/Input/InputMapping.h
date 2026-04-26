#ifndef INPUT_MAPPING_H
#define INPUT_MAPPING_H

#include <Engine/Input/InputDevice.h>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    class InputMapping final
    {
    private:
        InputDeviceType m_InputDeviceType{ InputDeviceType::None };
        std::unordered_map<std::string, SDL_Scancode> m_KeyboardMappings{};
        std::unordered_map<std::string, SDL_GamepadButton> m_GamepadMappings{};

    public:
        void SetInputDeviceType(InputDeviceType inputDeviceType)
        {
            m_InputDeviceType = inputDeviceType;
        }

        int GetInputKey(std::string const& actionName);

        void AddKeyboardMapping(std::string const& actionName, SDL_Scancode scancode)
        {
            m_KeyboardMappings[actionName] = scancode;
        }

        void AddGamepadMapping(std::string const& actionName, SDL_GamepadButton button)
        {
            m_GamepadMappings[actionName] = button;
        }

        void SetKeyboardMappings(std::unordered_map<std::string, SDL_Scancode> const& keyboardMappings)
        {
            m_KeyboardMappings = keyboardMappings;
        }

        void SetGamepadMappings(std::unordered_map<std::string, SDL_GamepadButton> const& gamepadMappings)
        {
            m_GamepadMappings = gamepadMappings;
        }

    };
}

#endif
