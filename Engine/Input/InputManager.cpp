#include <Engine/Components/ControllerComponent.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>
#include <SDL3/SDL_events.h>
#include <memory>
#include <utility>

using namespace GameEngine;

void InputManager::RegisterController(ControllerComponent* controller, InputDeviceType inputType)
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
        newControllerInfo.m_InputDevice = std::make_unique<GamepadInputDevice>();
        break;
    }

    m_PlayerControllers.push_back(std::move(newControllerInfo));
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
