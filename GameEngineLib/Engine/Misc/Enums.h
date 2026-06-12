#ifndef ENUMS_H
#define ENUMS_H

namespace GameEngine
{
    enum class Direction
    {
        Up,
        Level,
        Down,
        Left,
        Middle,
        Right
    };

    enum class Pivot
    {
        LeftUp,
        LeftLevel,
        LeftDown,
        MiddleUp,
        MiddleLevel,
        MiddleDown,
        RightUp,
        RightLevel,
        RightDown,
    };

    enum class InputActionType
    {
        Pressed,
        Released,
        Held,
        Down,
        Up,
    };

    enum class InputCode
    {
        NONE,
        KB_A,
        KB_B,
        KB_C,
        KB_D,
        KB_E,
        KB_F,
        KB_G,
        KB_H,
        KB_I,
        KB_J,
        KB_K,
        KB_L,
        KB_M,
        KB_N,
        KB_O,
        KB_P,
        KB_Q,
        KB_R,
        KB_S,
        KB_T,
        KB_U,
        KB_V,
        KB_W,
        KB_X,
        KB_Y,
        KB_Z,
        KB_1,
        KB_2,
        KB_3,
        KB_4,
        KB_5,
        KB_6,
        KB_7,
        KB_8,
        KB_9,
        KB_0,
        KB_RETURN,
        KB_ESC,
        KB_BACKSPACE,
        KB_TAB,
        KB_SPACE,
        KB_RIGHT,
        KB_LEFT,
        KB_UP,
        KB_DOWN,
        KB_LCTRL,
        KB_LSHIFT,
        KB_LALT,
        KB_RCTRL,
        KB_RSHIFT,
        KB_RALT,

        GP_BUTTON_SOUTH,
        GP_BUTTON_EAST,
        GP_BUTTON_WEST,
        GP_BUTTON_NORTH,
        GP_BUTTON_BACK,
        GP_BUTTON_GUIDE,
        GP_BUTTON_START,
        GP_BUTTON_LEFT_STICK,
        GP_BUTTON_RIGHT_STICK,
        GP_BUTTON_LEFT_SHOULDER,
        GP_BUTTON_RIGHT_SHOULDER,
        GP_BUTTON_DPAD_UP,
        GP_BUTTON_DPAD_DOWN,
        GP_BUTTON_DPAD_LEFT,
        GP_BUTTON_DPAD_RIGHT,
        GP_BUTTON_RIGHT_PADDLE1,
        GP_BUTTON_LEFT_PADDLE1,
        GP_BUTTON_RIGHT_PADDLE2,
        GP_BUTTON_LEFT_PADDLE2,
    };
}

#endif