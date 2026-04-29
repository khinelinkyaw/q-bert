#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_joystick.h>

#include "InputDevice.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <vector>

using namespace GameEngine;

bool InputDevice::IsPressed(int key) const
{
    return GetPreviousKeyState(key) && GetCurrentKeyState(key);
}

bool InputDevice::IsReleased(int key) const
{
    return GetPreviousKeyState(key) && GetCurrentKeyState(key);
}

bool InputDevice::IsHeld(int key) const
{
    return GetPreviousKeyState(key) && GetCurrentKeyState(key);
}

bool InputDevice::IsDown(int key) const
{
    return GetCurrentKeyState(key);
}

bool InputDevice::IsUp(int key) const
{
    return GetCurrentKeyState(key);
}

GameEngine::KeyboardInputDevice::KeyboardInputDevice()
{
    m_Type = InputDeviceType::Keyboard;
    m_KeyStatesPtr = SDL_GetKeyboardState(&m_NumKeys);

    m_KeyStates[0].resize(m_NumKeys);
    m_KeyStates[1].resize(m_NumKeys);
}

bool GameEngine::KeyboardInputDevice::GetPreviousKeyState(int key) const
{
    int previousStateIndex = 1 - m_CurrentStateIndex;
    return m_KeyStates[previousStateIndex][key];
}

bool GameEngine::KeyboardInputDevice::GetCurrentKeyState(int key) const
{
    return m_KeyStates[m_CurrentStateIndex][key];
}

void GameEngine::KeyboardInputDevice::UpdateState()
{
    int nextStateIndex{ 1 - m_CurrentStateIndex };

    SDL_PumpEvents();

    for (int i = 0; i < m_NumKeys; ++i)
    {
        m_KeyStates[nextStateIndex][i] = m_KeyStatesPtr[i];
    }

    m_CurrentStateIndex = nextStateIndex;
}

GameEngine::GamepadInputDevice::GamepadInputDevice(int playerIndex)
    : m_PlayerIndex{ playerIndex }
{
    m_Type = InputDeviceType::Gamepad;
}

bool GameEngine::GamepadInputDevice::GetPreviousKeyState(int key) const
{
    int previousStateIndex = 1 - m_CurrentStateIndex;

    return m_KeyStates[previousStateIndex][key];
}

bool GameEngine::GamepadInputDevice::GetCurrentKeyState(int key) const
{
    return m_KeyStates[m_CurrentStateIndex][key];
}

void GameEngine::GamepadInputDevice::RefreshGamepads()
{
    int joystickCount{ 0 };
    SDL_JoystickID* pJoystickIDs = SDL_GetGamepads(&joystickCount);

    for (int index = 0; index < joystickCount; ++index)
    {
        SDL_OpenGamepad(pJoystickIDs[index]);
    }
}

void GameEngine::GamepadInputDevice::UpdateState()
{
    int nextStateIndex{ 1 - m_CurrentStateIndex };

    SDL_Gamepad* pGamepad{ SDL_GetGamepadFromPlayerIndex(m_PlayerIndex) };

    if (pGamepad == nullptr)
    {
        RefreshGamepads();
        return;
    }

    for (int index = 0; index < m_NumButtons; ++index)
    {
        m_KeyStates[nextStateIndex][index] = SDL_GetGamepadButton(pGamepad, static_cast<SDL_GamepadButton>(index));
    }

    m_CurrentStateIndex = nextStateIndex;
}
