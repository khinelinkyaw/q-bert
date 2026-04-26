#include "InputMapping.h"
#include "InputDevice.h"

#include <string>

int GameEngine::InputMapping::GetInputKey(std::string const& actionName)
{
    switch (m_InputDeviceType)
    {
    case InputDeviceType::Keyboard:
        return static_cast<int>(m_KeyboardMappings[actionName]);
    case InputDeviceType::Gamepad:
        return static_cast<int>(m_GamepadMappings[actionName]);
    default:
        return -1;
    }
}
