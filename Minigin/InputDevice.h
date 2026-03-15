#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include "Components/ControllerComponent.h"
#include <memory>

namespace Engine
{
    enum class InputAction
    {
        MoveUp,
        MoveLeft,
        MoveDown,
        MoveRight,
    };

    enum class InputDeviceType
    {
        Keyboard,
        Gamepad
    };

    class InputDevice final
    {
    protected:
        class InputDeviceImpl;
        class KeyboardInputDeviceImpl;
        class GamepadInputDeviceImpl;
        InputDeviceImpl* m_Pimpl;

    public:
        bool IsPressed(InputAction action) const;
        bool IsReleased(InputAction action) const;
        bool IsHeld(InputAction action) const;
        bool IsDown(InputAction action) const;
        bool IsUp(InputAction action) const;

        void UpdateState();

        InputDevice(InputDeviceType inputDeviceType);
        ~InputDevice();
    };

    struct ControllerInfo final
    {
        ControllerComponent* m_PlayerController{ nullptr };
        InputDeviceType m_InputType{ InputDeviceType::Keyboard };
        std::unique_ptr<InputDevice> m_InputDevice{ nullptr };
    };

}

#endif
