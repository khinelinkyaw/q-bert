#ifndef __EMSCRIPTEN__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <Xinput.h>
#endif // __EMSCRIPTEN__

#include "InputDevice.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <array>
#include <unordered_map>
#include <vector>

using namespace Engine;

class InputDevice::InputDeviceImpl
{
protected:
    int m_CurrentStateIndex{ 0 };
    std::unordered_map<InputAction, int> m_Keymap{};
public:
    virtual bool GetPreviousKeyState(InputAction action) const = 0;
    virtual bool GetCurrentKeyState(InputAction action) const = 0;
    virtual void UpdateState() = 0;

    InputDeviceImpl() = default;
    virtual ~InputDeviceImpl() = default;
};

class InputDevice::KeyboardInputDeviceImpl final : public InputDevice::InputDeviceImpl
{
private:
    int m_NumKeys;
    std::array<std::vector<bool>, 2> m_KeyStates;
    bool const* m_KeyStatesPtr;

    bool GetPreviousKeyState(InputAction action) const override;
    bool GetCurrentKeyState(InputAction action) const override;
public:
    void UpdateState() override;

    KeyboardInputDeviceImpl();
    ~KeyboardInputDeviceImpl() override = default;
};

void InputDevice::KeyboardInputDeviceImpl::UpdateState()
{
    int l_NextStateIndex{ 1 - m_CurrentStateIndex };

    SDL_PumpEvents();

    for (int i = 0; i < m_NumKeys; ++i)
    {
        m_KeyStates[l_NextStateIndex][i] = m_KeyStatesPtr[i];
    }

    m_CurrentStateIndex = l_NextStateIndex;
}

bool InputDevice::KeyboardInputDeviceImpl::GetPreviousKeyState(InputAction action) const
{
    int l_PreviousStateIndex = 1 - m_CurrentStateIndex;
    int scancode = m_Keymap.at(action);

    return m_KeyStates[l_PreviousStateIndex][scancode];
}

bool InputDevice::KeyboardInputDeviceImpl::GetCurrentKeyState(InputAction action) const
{
    int scancode = m_Keymap.at(action);

    return m_KeyStates[m_CurrentStateIndex][scancode];
}

InputDevice::KeyboardInputDeviceImpl::KeyboardInputDeviceImpl()
    : m_NumKeys{}
    , m_KeyStates{}
    , m_KeyStatesPtr(SDL_GetKeyboardState(&m_NumKeys))

{
    // TODO: make this configurable
    m_Keymap = {
        { InputAction::MoveUp, SDL_SCANCODE_W },
        { InputAction::MoveLeft, SDL_SCANCODE_A },
        { InputAction::MoveDown, SDL_SCANCODE_S },
        { InputAction::MoveRight, SDL_SCANCODE_D }
    };

    m_KeyStates[0].resize(m_NumKeys);
    m_KeyStates[1].resize(m_NumKeys);
}



#ifndef __EMSCRIPTEN__
class InputDevice::GamepadInputDeviceImpl final : public InputDevice::InputDeviceImpl
{
private:
    DWORD m_ControllerIndex;
    std::array<XINPUT_STATE, 2> m_KeyStates;

    bool GetPreviousKeyState(InputAction action) const override;
    bool GetCurrentKeyState(InputAction action) const override;

public:
    void UpdateState() override;

    GamepadInputDeviceImpl(int controllerIndex = 0);
    ~GamepadInputDeviceImpl() override = default;
};


void InputDevice::GamepadInputDeviceImpl::UpdateState()
{
    int l_NextStateIndex{ 1 - m_CurrentStateIndex };

    ZeroMemory(&m_KeyStates[l_NextStateIndex], sizeof(XINPUT_STATE));
    XInputGetState(m_ControllerIndex, &m_KeyStates[l_NextStateIndex]);

    m_CurrentStateIndex = l_NextStateIndex;
}

InputDevice::GamepadInputDeviceImpl::GamepadInputDeviceImpl(int controllerIndex)
    : m_ControllerIndex(controllerIndex)
    , m_KeyStates{}
{
    // TODO: make this default parameter (better API visibility)
    // TODO: make this configurable
    // လုပ်စရာတွေ အများကြီးရှိသေးတယ်။
    m_Keymap = {
        { InputAction::MoveUp, XINPUT_GAMEPAD_DPAD_UP },
        { InputAction::MoveLeft, XINPUT_GAMEPAD_DPAD_LEFT },
        { InputAction::MoveDown, XINPUT_GAMEPAD_DPAD_DOWN },
        { InputAction::MoveRight, XINPUT_GAMEPAD_DPAD_RIGHT }
    };
}

bool InputDevice::GamepadInputDeviceImpl::GetPreviousKeyState(InputAction action) const
{
    int l_PreviousStateIndex = 1 - m_CurrentStateIndex;
    int button = m_Keymap.at(action);

    return m_KeyStates[l_PreviousStateIndex].Gamepad.wButtons & button;
}

bool InputDevice::GamepadInputDeviceImpl::GetCurrentKeyState(InputAction action) const
{
    int button = m_Keymap.at(action);

    return m_KeyStates[m_CurrentStateIndex].Gamepad.wButtons & button;
}
#else
class InputDevice::GamepadInputDeviceImpl final : public InputDevice::InputDeviceImpl
{
private:
    constexpr static int m_NumButtons{ 4 };
    SDL_Gamepad* m_pGamepad;
    std::array<std::array<bool, m_NumButtons>, 2> m_KeyStates;

    bool GetPreviousKeyState(InputAction action) const override;
    bool GetCurrentKeyState(InputAction action) const override;

public:
    void UpdateState() override;

    GamepadInputDeviceImpl();
    ~GamepadInputDeviceImpl() override = default;
};

InputDevice::GamepadInputDeviceImpl::GamepadInputDeviceImpl()
    : m_pGamepad{}
    , m_KeyStates{}
{
    int l_JoystickCount{ 0 };
    SDL_JoystickID* pJoystickIDs = SDL_GetGamepads(&l_JoystickCount);

    for (int i = 0; i < l_JoystickCount; ++i)
    {
        SDL_Gamepad* pGamepad = SDL_OpenGamepad(pJoystickIDs[i]);
        if (pGamepad != nullptr)
        {
            m_pGamepad = pGamepad;
            break;
        }
    }

    // TODO: make this default parameter (better API visibility)
    // TODO: make this configurable
    // လုပ်စရာတွေ အများကြီးရှိသေးတယ်။
    m_Keymap = {
        { InputAction::MoveUp, SDL_GAMEPAD_BUTTON_DPAD_UP },
        { InputAction::MoveLeft, SDL_GAMEPAD_BUTTON_DPAD_LEFT },
        { InputAction::MoveDown, SDL_GAMEPAD_BUTTON_DPAD_DOWN },
        { InputAction::MoveRight, SDL_GAMEPAD_BUTTON_DPAD_RIGHT }
    };
}

void InputDevice::GamepadInputDeviceImpl::UpdateState()
{
    int l_NextStateIndex{ 1 - m_CurrentStateIndex };

    for (int i = 0; i < m_NumButtons; ++i)
    {
        SDL_GamepadButton l_SDLButton = static_cast<SDL_GamepadButton>(m_Keymap.at(static_cast<InputAction>(i)));
        m_KeyStates[l_NextStateIndex][i] = SDL_GetGamepadButton(m_pGamepad, l_SDLButton);
    }

    m_CurrentStateIndex = l_NextStateIndex;
}

bool InputDevice::GamepadInputDeviceImpl::GetPreviousKeyState(InputAction action) const
{
    int l_PreviousStateIndex = 1 - m_CurrentStateIndex;
    int l_SDLButtonIndex = static_cast<int>(action);

    return m_KeyStates[l_PreviousStateIndex][l_SDLButtonIndex];
}

bool InputDevice::GamepadInputDeviceImpl::GetCurrentKeyState(InputAction action) const
{
    int l_SDLButtonIndex = static_cast<int>(action);

    return m_KeyStates[m_CurrentStateIndex][l_SDLButtonIndex];
}
#endif



InputDevice::InputDevice(InputDeviceType inputDeviceType)
    : m_Pimpl{}
{
    switch (inputDeviceType)
    {
        case InputDeviceType::Keyboard:
            m_Pimpl = new KeyboardInputDeviceImpl();
            break;
        case InputDeviceType::Gamepad:
            m_Pimpl = new GamepadInputDeviceImpl();
            break;
    }
}

InputDevice::~InputDevice()
{
    if (m_Pimpl != nullptr)
    {
        delete m_Pimpl;
        m_Pimpl = nullptr;
    }
}

bool InputDevice::IsPressed(InputAction action) const
{
    return !m_Pimpl->GetPreviousKeyState(action) && m_Pimpl->GetCurrentKeyState(action);
}

bool InputDevice::IsReleased(InputAction action) const
{
    return m_Pimpl->GetPreviousKeyState(action) && !m_Pimpl->GetCurrentKeyState(action);
}

bool InputDevice::IsHeld(InputAction action) const
{
    return m_Pimpl->GetPreviousKeyState(action) && m_Pimpl->GetCurrentKeyState(action);
}

bool InputDevice::IsDown(InputAction action) const
{
    return m_Pimpl->GetCurrentKeyState(action);
}

bool InputDevice::IsUp(InputAction action) const
{
    return !m_Pimpl->GetCurrentKeyState(action);
}

void InputDevice::UpdateState()
{
    m_Pimpl->UpdateState();
}
