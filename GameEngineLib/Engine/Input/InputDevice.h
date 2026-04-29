#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <SDL3/SDL_gamepad.h>
#include <array>
#include <vector>

namespace GameEngine
{
    enum class InputDeviceType
    {
        None,
        Keyboard,
        Gamepad
    };

    class InputDevice
    {
    protected:
        int m_CurrentStateIndex{ 0 };
        InputDeviceType m_Type{ InputDeviceType::None };

        virtual bool GetPreviousKeyState(int key) const = 0;
        virtual bool GetCurrentKeyState(int key) const = 0;

    public:
        bool IsPressed(int key) const;
        bool IsReleased(int key) const;
        bool IsHeld(int key) const;
        bool IsDown(int key) const;
        bool IsUp(int key) const;

        InputDeviceType GetType() const { return m_Type; }

        virtual void UpdateState() = 0;

        InputDevice() = default;
        virtual ~InputDevice() = default;
    };

    class KeyboardInputDevice final : public InputDevice
    {
    private:
        int m_NumKeys{};
        std::array<std::vector<bool>, 2> m_KeyStates{};
        bool const* m_KeyStatesPtr{};

        virtual bool GetPreviousKeyState(int key) const override;
        virtual bool GetCurrentKeyState(int key) const override;
    public:
        void UpdateState() override;

        KeyboardInputDevice();
        ~KeyboardInputDevice() override = default;
    };

    class GamepadInputDevice final : public InputDevice
    {
    private:
        static int constexpr m_NumButtons{ SDL_GAMEPAD_BUTTON_COUNT + 1 };
        std::array<std::array<bool, m_NumButtons>, 2> m_KeyStates{};
        int m_PlayerIndex{-1};

        bool GetPreviousKeyState(int key) const override;
        bool GetCurrentKeyState(int key) const override;

    public:
        static void RefreshGamepads();

        void UpdateState() override;
        int GetPlayerIndex() const { return m_PlayerIndex; }

        GamepadInputDevice() = default;
        GamepadInputDevice(int playerIndex);
        ~GamepadInputDevice() override = default;
    };
}

#endif
