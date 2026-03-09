#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Components/ControllerComponent.h"
#include "Singleton.h"
//#include <Xinput.h>

namespace dae
{
    class InputManager final : public Singleton<InputManager>
    {
    private:
    public:
        ControllerComponent* m_PlayerOneObjController{};
        bool ProcessInput();
    };
}

#endif