#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_scancode.h>

#include "InputDevice.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <array>
#include <unordered_map>
#include <vector>

using namespace GameEngine;

bool InputDevice::IsPressed(InputAction action) const
{
    return GetPreviousKeyState(action) && GetCurrentKeyState(action);
}

bool InputDevice::IsReleased(InputAction action) const
{
    return GetPreviousKeyState(action) && GetCurrentKeyState(action);
}

bool InputDevice::IsHeld(InputAction action) const
{
    return GetPreviousKeyState(action) && GetCurrentKeyState(action);
}

bool InputDevice::IsDown(InputAction action) const
{
    return GetCurrentKeyState(action);
}

bool InputDevice::IsUp(InputAction action) const
{
    return GetCurrentKeyState(action);
}

GameEngine::KeyboardInputDevice::KeyboardInputDevice()
{
    m_KeyStatesPtr = SDL_GetKeyboardState(&m_NumKeys);

    // TODO: make this configurable
    m_Keymap = {
        { InputAction::MoveUp, SDL_SCANCODE_W },
        { InputAction::MoveLeft, SDL_SCANCODE_A },
        { InputAction::MoveDown, SDL_SCANCODE_S },
        { InputAction::MoveRight, SDL_SCANCODE_D },
        { InputAction::TakeDamage, SDL_SCANCODE_X},
        { InputAction::IncreaseScore, SDL_SCANCODE_Z }
    };

    m_KeyStates[0].resize(m_NumKeys);
    m_KeyStates[1].resize(m_NumKeys);
}

bool GameEngine::KeyboardInputDevice::GetPreviousKeyState(InputAction action) const
{
    int previousStateIndex = 1 - m_CurrentStateIndex;
    int scancode = m_Keymap.at(action);

    return m_KeyStates[previousStateIndex][scancode];
}

bool GameEngine::KeyboardInputDevice::GetCurrentKeyState(InputAction action) const
{
    int scancode = m_Keymap.at(action);

    return m_KeyStates[m_CurrentStateIndex][scancode];
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
    // TODO: make this default parameter (better API visibility)
    // TODO: make this configurable
    m_Keymap = {
        { InputAction::MoveUp, SDL_GAMEPAD_BUTTON_DPAD_UP },
        { InputAction::MoveLeft, SDL_GAMEPAD_BUTTON_DPAD_LEFT },
        { InputAction::MoveDown, SDL_GAMEPAD_BUTTON_DPAD_DOWN },
        { InputAction::MoveRight, SDL_GAMEPAD_BUTTON_DPAD_RIGHT },
        { InputAction::TakeDamage, SDL_GAMEPAD_BUTTON_SOUTH },
        { InputAction::IncreaseScore, SDL_GAMEPAD_BUTTON_NORTH}
    };
}

bool GameEngine::GamepadInputDevice::GetPreviousKeyState(InputAction action) const
{
    int previousStateIndex = 1 - m_CurrentStateIndex;
    int SDLButtonIndex = static_cast<int>(action);

    return m_KeyStates[previousStateIndex][SDLButtonIndex];
}

bool GameEngine::GamepadInputDevice::GetCurrentKeyState(InputAction action) const
{
    int SDLButtonIndex = static_cast<int>(action);

    return m_KeyStates[m_CurrentStateIndex][SDLButtonIndex];
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
        SDL_GamepadButton SDLButton = static_cast<SDL_GamepadButton>(m_Keymap.at(static_cast<InputAction>(index)));
        
        // Might throw an exception if the gamepad is disconnected during the update, 
        // but this is a rare edge case and can be handled by refreshing the gamepads in the next update
        m_KeyStates[nextStateIndex][index] = SDL_GetGamepadButton(pGamepad, SDLButton);
    }

    m_CurrentStateIndex = nextStateIndex;
}
