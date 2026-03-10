#include "Command.h"
#include "Components/ControllerComponent.h"
#include "InputManager.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
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

bool dae::KeyboardInputDevice::IsPressed(InputAction action) const
{
    return GetPreviousKeyState(action) == false && GetCurrentKeyState(action) == true;
}

bool dae::KeyboardInputDevice::IsReleased(InputAction action) const
{
    return GetPreviousKeyState(action) == true && GetCurrentKeyState(action) == false;
}

bool dae::KeyboardInputDevice::IsHeld(InputAction action) const
{
    return GetPreviousKeyState(action) == true && GetCurrentKeyState(action) == true;
}

bool dae::KeyboardInputDevice::IsDown(InputAction action) const
{
    return GetCurrentKeyState(action);
}

bool dae::KeyboardInputDevice::IsUp(InputAction action) const
{
    return !GetCurrentKeyState(action);
}

dae::KeyboardInputDevice::KeyboardInputDevice()
    : m_NumKeys{}
    , m_CurrentStateIndex{}
    , m_KeyStates{}
    , m_KeyStatesPtr(SDL_GetKeyboardState(&m_NumKeys))
    , m_Keymap{
        { InputAction::MoveUp, SDL_SCANCODE_W },
        { InputAction::MoveLeft, SDL_SCANCODE_A },
        { InputAction::MoveDown, SDL_SCANCODE_S },
        { InputAction::MoveRight, SDL_SCANCODE_D }
    }
{
    m_KeyStates[0].resize(m_NumKeys);
    m_KeyStates[1].resize(m_NumKeys);
}
