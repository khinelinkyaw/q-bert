#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>

#include <SDL3/SDL_events.h>

using namespace GameEngine;

GamepadInputDevice& GameEngine::InputManager::GetGamepadInputDevice(int playerIndex)
{
    for (GamepadInputDevice& gamepadInputDevice : m_GamepadInputDevices)
    {
        if (gamepadInputDevice.GetPlayerIndex() == playerIndex)
        {
            return gamepadInputDevice;
        }
    }

    GamepadInputDevice::RefreshGamepads();

    m_GamepadInputDevices.emplace_back(playerIndex);
    return m_GamepadInputDevices.back();
}

bool InputManager::ProcessInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            return false;
        }
    }

    m_KeyboardInputDevice.UpdateState();

    for (GamepadInputDevice& gamepadInputDevice : m_GamepadInputDevices)
    {
        gamepadInputDevice.UpdateState();
    }

    return true;
}
