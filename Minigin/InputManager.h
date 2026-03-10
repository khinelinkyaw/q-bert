#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Components/ControllerComponent.h"
#include "Singleton.h"
#include <Xinput.h>
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
        virtual ~InputDevice() = default;
    };

    class KeyboardInputDevice final : public InputDevice
    {
    private:
        int m_NumKeys;
        std::array<std::vector<bool>, 2> m_KeyStates;
        bool const* m_KeyStatesPtr;

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
        DWORD m_ControllerIndex;
        std::array<XINPUT_STATE, 2> m_KeyStates;

        bool GetPreviousKeyState(InputAction action) const override;
        bool GetCurrentKeyState(InputAction action) const override;

    public:
        void UpdateState() override;

        GamepadInputDevice(int controllerIndex);
        ~GamepadInputDevice() override = default;
    };

    struct ControllerInfo final
    {
        ControllerComponent* m_PlayerController{ nullptr };
        InputDeviceType m_InputType{ InputDeviceType::Keyboard };
        std::unique_ptr<InputDevice> m_InputDevice{ nullptr };
    };

    class InputManager final : public Singleton<InputManager>
    {
    private:
        std::vector<ControllerInfo> m_PlayerControllers{};

    public:
        void RegisterController(ControllerComponent* controller, InputDeviceType inputType = InputDeviceType::Keyboard);
        bool ProcessInput();
    };
}

#endif