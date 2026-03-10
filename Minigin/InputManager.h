#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Components/ControllerComponent.h"
#include "Singleton.h"
#include <SDL3/SDL_keyboard.h>
//#include <Xinput.h>

namespace dae
{
    class InputManager final : public Singleton<InputManager>
    {
    private:
        bool const* m_KeyStates{ SDL_GetKeyboardState(nullptr) };
    public:
        ControllerComponent* m_PlayerOneObjController{};
        bool ProcessInput();
    };
}

#endif