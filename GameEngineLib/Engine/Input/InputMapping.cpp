#include "InputMapping.h"

#include <Engine/Misc/Constants.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputDevice.h>

#include <string>

bool GameEngine::InputMapping::GetActionState(std::string const& actionName) const
{
    auto actionMappingIter{ m_ActionMappings.find(actionName) };

    if (actionMappingIter == m_ActionMappings.end())
        return false;

    ActionMapping actionMapping{ actionMappingIter->second };

    InputCode inputCode{ InputCode::NONE };

    switch (m_InputDevice->GetType())
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
        return m_InputDevice->IsPressed(underlyingCode);
    case InputActionType::Released:
        return m_InputDevice->IsReleased(underlyingCode);
    case InputActionType::Held:
        return m_InputDevice->IsHeld(underlyingCode);
    case InputActionType::Down:
        return m_InputDevice->IsDown(underlyingCode);
    case InputActionType::Up:
        return m_InputDevice->IsUp(underlyingCode);
    }

    return false;
}

GameEngine::InputMapping::InputMapping()
    : m_InputDevice{ &InputManager::GetInstance().GetNullInputDevice() }
{
}
