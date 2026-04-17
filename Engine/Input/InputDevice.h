#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <Engine/Components/ControllerComponent.h>
#include <memory>

namespace GameEngine
{
    enum class InputAction
    {
        MoveUp,
        MoveLeft,
        MoveDown,
        MoveRight,
        TakeDamage,
        IncreaseScore
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
        std::unique_ptr<InputDeviceImpl> m_Pimpl;

        InputDevice(std::unique_ptr<InputDeviceImpl>&& pimpl);
    public:
        bool IsPressed(InputAction action) const;
        bool IsReleased(InputAction action) const;
        bool IsHeld(InputAction action) const;
        bool IsDown(InputAction action) const;
        bool IsUp(InputAction action) const;

        void UpdateState();

        virtual ~InputDevice();
    };

    class KeyboardInputDevice final: public InputDevice
    {
    private:
        class KeyboardImpl;
        
    public:
        KeyboardInputDevice();
        ~KeyboardInputDevice() override = default;
    };

    class GamepadInputDevice final: public InputDevice
    {
    private:
        class GamepadImpl;

    public:
        GamepadInputDevice();
        ~GamepadInputDevice() override = default;
    };

    struct ControllerInfo final
    {
        ControllerComponent* m_PlayerController{ nullptr };
        InputDeviceType m_InputType{ InputDeviceType::Keyboard };
        std::unique_ptr<InputDevice> m_InputDevice{ nullptr };
    };

}

#endif
