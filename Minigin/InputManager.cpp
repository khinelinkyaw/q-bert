#include "Command.h"
#include "InputManager.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>

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

    SDL_PumpEvents();

    if (m_KeyStates[SDL_SCANCODE_W])
    {
        m_PlayerOneObjController->AddCommand<MoveCommand>(0.f, -3.0f);
    }
    if (m_KeyStates[SDL_SCANCODE_A])
    {
        m_PlayerOneObjController->AddCommand<MoveCommand>(-3.f, 0.0f);
    }
    if (m_KeyStates[SDL_SCANCODE_S])
    {
        m_PlayerOneObjController->AddCommand<MoveCommand>(0.f, 3.0f);
    }
    if (m_KeyStates[SDL_SCANCODE_D])
    {
        m_PlayerOneObjController->AddCommand<MoveCommand>(3.f, 0.0f);
    }

    return true;
}
