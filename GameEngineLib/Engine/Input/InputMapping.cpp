#include "InputMapping.h"
#include "InputDevice.h"

#include <string>

int GameEngine::InputMapping::GetInputKey(std::string const& actionName)
{
    switch (m_InputDeviceType)
    {
    case InputDeviceType::Keyboard:
        return static_cast<int>(m_ActionMappings[actionName].first);
    case InputDeviceType::Gamepad:
        return static_cast<int>(m_ActionMappings[actionName].second);
    default:
        return -1;
    }
}
