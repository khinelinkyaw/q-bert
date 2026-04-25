#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Engine/Input/InputDevice.h>
#include <Engine/Misc/Singleton.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
    class ControllerComponent;
    class InputManager final : public Singleton<InputManager>
    {
    private:
        enum class InputSlot
        {
            Keyboard,
            Controller0,
            Controller1,
            Controller2,
            Controller3,
        };

        std::vector<ControllerInfo> m_PlayerControllers;
        std::unordered_map<InputSlot, std::unique_ptr<InputDevice>> m_InputDevices;

    public:
        InputDevice* GetInputDevice(InputManager::InputSlot inputSlot);

        void RegisterController(ControllerComponent* controller, InputDeviceType inputType = InputDeviceType::Keyboard);
        bool ProcessInput();

        InputManager();
        ~InputManager() override = default;
    };
}

#endif