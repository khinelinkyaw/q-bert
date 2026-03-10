#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Components/ControllerComponent.h"
#include "Singleton.h"
//#include <Xinput.h>
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

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
    public:
        virtual bool IsPressed(InputAction action) const = 0;
        virtual bool IsReleased(InputAction action) const = 0;
        virtual bool IsHeld(InputAction action) const = 0;
        virtual bool IsDown(InputAction action) const = 0;
        virtual bool IsUp(InputAction action) const = 0;

        virtual void UpdateState() = 0;

        virtual ~InputDevice() = default;
    };

    class KeyboardInputDevice final : public InputDevice
    {
    private:
        int m_NumKeys;
        int m_CurrentStateIndex;
        std::array<std::vector<bool>, 2> m_KeyStates;
        bool const* m_KeyStatesPtr;
        std::unordered_map<InputAction, int> m_Keymap;

        bool GetPreviousKeyState(InputAction action) const;
        bool GetCurrentKeyState(InputAction action) const;
    public:
        bool IsPressed(InputAction action) const override;
        bool IsReleased(InputAction action) const override;
        bool IsHeld(InputAction action) const override;
        bool IsDown(InputAction action) const override;
        bool IsUp(InputAction action) const override;

        void UpdateState() override;

        KeyboardInputDevice();
        ~KeyboardInputDevice() override = default;
    };

    struct ControllerInfo final
    {
        ControllerComponent* m_PlayerController{ nullptr };
        InputDeviceType m_InputType{ InputDeviceType::Keyboard };
        std::unique_ptr<InputDevice> m_InputDevice{ nullptr };

        void ProcessInput();
        void UpdateKeyStates();
    };

    class InputManager final : public Singleton<InputManager>
    {
    private:
        std::array<ControllerInfo, 2> m_PlayerControllers{};

    public:
        void RegisterController(size_t playerIndex, ControllerComponent* controller, InputDeviceType inputType = InputDeviceType::Keyboard);
        bool ProcessInput();
    };
}

#endif