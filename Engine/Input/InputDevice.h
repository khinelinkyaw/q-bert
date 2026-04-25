#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <Engine/Components/ControllerComponent.h>
#include <SDL3/SDL_gamepad.h>
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

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
        int m_CurrentStateIndex{ 0 };
        std::unordered_map<InputAction, int> m_Keymap{};

        virtual bool GetPreviousKeyState(InputAction action) const = 0;
        virtual bool GetCurrentKeyState(InputAction action) const = 0;

    public:
        bool IsPressed(InputAction action) const;
        bool IsReleased(InputAction action) const;
        bool IsHeld(InputAction action) const;
        bool IsDown(InputAction action) const;
        bool IsUp(InputAction action) const;

        virtual void UpdateState() = 0;

        InputDevice() = default;
        InputDevice(InputDevice const& other) = delete;
        InputDevice(InputDevice&& other) = delete;
        InputDevice& operator=(InputDevice const& other) = delete;
        InputDevice& operator=(InputDevice&& other) = delete;
        virtual ~InputDevice() = default;
    };

    class KeyboardInputDevice final : public InputDevice
    {
    private:
        int m_NumKeys{};
        std::array<std::vector<bool>, 2> m_KeyStates{};
        bool const* m_KeyStatesPtr{};

        bool GetPreviousKeyState(InputAction action) const override;
        bool GetCurrentKeyState(InputAction action) const override;
    public:
        void UpdateState() override;

        KeyboardInputDevice();
        ~KeyboardInputDevice() override = default;
    };

    class GamepadInputDevice final : public InputDevice
    {
    private:
        static int constexpr m_NumButtons{ 6 };
        std::array<std::array<bool, m_NumButtons>, 2> m_KeyStates{};
        SDL_Gamepad* m_pGamepad{};

        bool GetPreviousKeyState(InputAction action) const override;
        bool GetCurrentKeyState(InputAction action) const override;

    public:
        void UpdateState() override;

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
