#include "Command.h"
#include "InputManager.h"
#include "Modules/Transform.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <memory>
#include <utility>

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
            bool const* keyStates = SDL_GetKeyboardState(nullptr);

            if (keyStates[SDL_SCANCODE_W])
            {
                std::unique_ptr<ObjectCommand> moveUp{ std::make_unique<MoveCommand>() };
                static_cast<MoveCommand*>(moveUp.get())->SetMovement(Transform{ 0.f, -1.0f });
                //moveUp->SetMovement(Transform{ 0.f, -1.0f });
                m_PlayerOneObjController->AddCommand(std::move(moveUp));
            }
            if (keyStates[SDL_SCANCODE_A])
            {
                MoveCommand moveLeft{};
                moveLeft.SetMovement(Transform{ -1.f, 0.0f });
                m_PlayerOneObjController->AddCommand(std::make_unique<MoveCommand>(moveLeft));
            }
            if (keyStates[SDL_SCANCODE_S])
            {
                MoveCommand moveDown{};
                moveDown.SetMovement(Transform{ 0.f, 1.0f });
                m_PlayerOneObjController->AddCommand(std::make_unique<MoveCommand>(moveDown));
            }
            if (keyStates[SDL_SCANCODE_D])
            {
                MoveCommand moveRight{};
                moveRight.SetMovement(Transform{ 0.f, 1.0f });
                m_PlayerOneObjController->AddCommand(std::make_unique<MoveCommand>(moveRight));
            }
        }
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {

        }
        // etc...
    }



    return true;
}
