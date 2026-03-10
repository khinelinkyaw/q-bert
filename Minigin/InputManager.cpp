#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Components/ControllerComponent.h"
#include "InputManager.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <Xinput.h>
#include <memory>
#include <utility>


void dae::InputManager::RegisterController(ControllerComponent* controller, InputDeviceType inputType)
{
    struct ControllerInfo newControllerInfo {};

    newControllerInfo.m_PlayerController = controller;
    newControllerInfo.m_InputType = inputType;

    switch (inputType)
    {
    case InputDeviceType::Keyboard:
        newControllerInfo.m_InputDevice = std::make_unique<KeyboardInputDevice>();
        break;
    case InputDeviceType::Gamepad:
        newControllerInfo.m_InputDevice = std::make_unique<GamepadInputDevice>(0);
        break;
    }

    m_PlayerControllers.push_back(std::move(newControllerInfo));
}

bool dae::InputManager::ProcessInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            return false;
        }
        if (e.type == SDL_EVENT_KEY_DOWN)
        {
        }
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {

        }
        // etc...
    }

    for (ControllerInfo& controllerInfo : m_PlayerControllers)
    {
        controllerInfo.m_InputDevice->UpdateState();
        controllerInfo.m_PlayerController->ProcessInput(*controllerInfo.m_InputDevice);
    }

    return true;
}

void dae::KeyboardInputDevice::UpdateState()
{
    int l_NextStateIndex{ 1 - m_CurrentStateIndex };

    SDL_PumpEvents();

    for (int i = 0; i < m_NumKeys; ++i)
    {
        m_KeyStates[l_NextStateIndex][i] = m_KeyStatesPtr[i];
    }

    m_CurrentStateIndex = l_NextStateIndex;
}

bool dae::KeyboardInputDevice::GetPreviousKeyState(InputAction action) const
{
    int l_PreviousStateIndex = 1 - m_CurrentStateIndex;
    int scancode = m_Keymap.at(action);

    return m_KeyStates[l_PreviousStateIndex][scancode];
}

bool dae::KeyboardInputDevice::GetCurrentKeyState(InputAction action) const
{
    int scancode = m_Keymap.at(action);

    return m_KeyStates[m_CurrentStateIndex][scancode];
}

bool dae::InputDevice::IsPressed(InputAction action) const
{
    return !GetPreviousKeyState(action) && GetCurrentKeyState(action);
}

bool dae::InputDevice::IsReleased(InputAction action) const
{
    return GetPreviousKeyState(action) && !GetCurrentKeyState(action);
}

bool dae::InputDevice::IsHeld(InputAction action) const
{
    return GetPreviousKeyState(action) && GetCurrentKeyState(action);
}

bool dae::InputDevice::IsDown(InputAction action) const
{
    return GetCurrentKeyState(action);
}

bool dae::InputDevice::IsUp(InputAction action) const
{
    return !GetCurrentKeyState(action);
}

dae::KeyboardInputDevice::KeyboardInputDevice()
    : m_NumKeys{}
    , m_KeyStates{}
    , m_KeyStatesPtr(SDL_GetKeyboardState(&m_NumKeys))

{
    // TODO: make this configurableZ
    m_Keymap = {
        { InputAction::MoveUp, SDL_SCANCODE_W },
        { InputAction::MoveLeft, SDL_SCANCODE_A },
        { InputAction::MoveDown, SDL_SCANCODE_S },
        { InputAction::MoveRight, SDL_SCANCODE_D }
    };

    m_KeyStates[0].resize(m_NumKeys);
    m_KeyStates[1].resize(m_NumKeys);
}

void dae::GamepadInputDevice::UpdateState()
{
    int l_NextStateIndex{ 1 - m_CurrentStateIndex };

    ZeroMemory(&m_KeyStates[l_NextStateIndex], sizeof(XINPUT_STATE));
    XInputGetState(m_ControllerIndex, &m_KeyStates[l_NextStateIndex]);

    m_CurrentStateIndex = l_NextStateIndex;
}

dae::GamepadInputDevice::GamepadInputDevice(int controllerIndex)
    : m_ControllerIndex(controllerIndex)
    , m_KeyStates{}
{
    // TODO: make this default parameter (better API visibility)
    // TODO: make this configurable
    m_Keymap = {
        { InputAction::MoveUp, XINPUT_GAMEPAD_DPAD_UP },
        { InputAction::MoveLeft, XINPUT_GAMEPAD_DPAD_LEFT },
        { InputAction::MoveDown, XINPUT_GAMEPAD_DPAD_DOWN },
        { InputAction::MoveRight, XINPUT_GAMEPAD_DPAD_RIGHT }
    };
}

bool dae::GamepadInputDevice::GetPreviousKeyState(InputAction action) const
{
    int l_PreviousStateIndex = 1 - m_CurrentStateIndex;
    int button = m_Keymap.at(action);

    return m_KeyStates[l_PreviousStateIndex].Gamepad.wButtons & button;
}

bool dae::GamepadInputDevice::GetCurrentKeyState(InputAction action) const
{
    int button = m_Keymap.at(action);

    return m_KeyStates[m_CurrentStateIndex].Gamepad.wButtons & button;
}