#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include "Components/ControllerComponent.h"
#include <memory>

namespace dae
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

    class InputDevice
    {
    protected:
        class InputDeviceImpl;
        class KeyboardInputDeviceImpl;
        class GamepadInputDeviceImpl;
        std::unique_ptr<InputDeviceImpl> m_Pimpl;

    public:
        bool IsPressed(InputAction action) const;
        bool IsReleased(InputAction action) const;
        bool IsHeld(InputAction action) const;
        bool IsDown(InputAction action) const;
        bool IsUp(InputAction action) const;

        virtual void UpdateState();

        InputDevice(InputDeviceType inputDeviceType);
        virtual ~InputDevice() = default;

    };

    struct ControllerInfo final
    {
        ControllerComponent* m_PlayerController{ nullptr };
        InputDeviceType m_InputType{ InputDeviceType::Keyboard };
        std::unique_ptr<InputDevice> m_InputDevice{ nullptr };
    };

}

#endif
