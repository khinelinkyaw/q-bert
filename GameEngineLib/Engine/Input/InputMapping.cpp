#include "InputMapping.h"

#include <Engine/Misc/Constants.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Input/InputDevice.h>

#include <string>

bool GameEngine::InputMapping::GetActionState(std::string const& actionName, InputDevice const& inputDevice) const
{
    auto actionMappingIter{ m_ActionMappings.find(actionName) };

    if (actionMappingIter == m_ActionMappings.end())
        return false;

    ActionMapping actionMapping{ actionMappingIter->second };

    InputCode inputCode{ InputCode::NONE };

    switch (inputDevice.GetType())
    {
    case InputDeviceType::None:
        return false;
    case InputDeviceType::Keyboard:
        inputCode = actionMapping.keyboardCode;
        break;
    case InputDeviceType::Gamepad:
        inputCode = actionMapping.gamepadCode;
        break;
    }

    if (inputCode == InputCode::NONE)
    {
        return false;
    }

    int underlyingCode{ Constants::INPUT_CODE_MAP.at(inputCode) };

    switch (actionMapping.actionType)
    {
    case InputActionType::Pressed:
        return inputDevice.IsPressed(underlyingCode);
    case InputActionType::Released:
        return inputDevice.IsReleased(underlyingCode);
    case InputActionType::Held:
        return inputDevice.IsHeld(underlyingCode);
    case InputActionType::Down:
        return inputDevice.IsDown(underlyingCode);
    case InputActionType::Up:
        return inputDevice.IsUp(underlyingCode);
    }

    return false;
}