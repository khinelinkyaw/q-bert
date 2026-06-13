#ifndef ENUMS_H
#define ENUMS_H

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

namespace GameEngine
{
    using json = nlohmann::json;

    enum class AnimationType
    {
        Once,
        Loop
    };

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

    NLOHMANN_JSON_SERIALIZE_ENUM(Pivot,
    {
        { Pivot::LeftUp,      "LeftUp"},        // 0
        { Pivot::LeftLevel,   "LeftLevel"},     // 1
        { Pivot::LeftDown,    "LeftDown"},      // 2

        { Pivot::MiddleUp,    "MiddleUp"},      // 3
        { Pivot::MiddleLevel, "MiddleLevel"},   // 4
        { Pivot::MiddleDown,  "MiddleDown"},    // 5

        { Pivot::RightUp,     "RightUp"},       // 6
        { Pivot::RightLevel,  "RightLevel"},    // 7
        { Pivot::RightDown,   "RightDown"}      // 8
    })

    enum class InputActionType
    {
        Pressed,
        Released,
        Held,
        Down,
        Up,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(InputActionType,
    {
        {InputActionType::Pressed, "Pressed"},
        {InputActionType::Released, "Released"},
        {InputActionType::Held, "Held"},
        {InputActionType::Down, "Down"},
        {InputActionType::Up, "Up"}
    })

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
        KB_F1,
        KB_F2,
        KB_F3,
        KB_F4,
        KB_F5,
        KB_F6,
        KB_F7,
        KB_F8,
        KB_F9,
        KB_F10,
        KB_F11,
        KB_F12,

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

    NLOHMANN_JSON_SERIALIZE_ENUM(InputCode,
    {
        { InputCode::NONE,                      "NONE" },
        { InputCode::KB_A,                      "KB_A" },
        { InputCode::KB_B,                      "KB_B" },
        { InputCode::KB_C,                      "KB_C" },
        { InputCode::KB_D,                      "KB_D" },
        { InputCode::KB_E,                      "KB_E" },
        { InputCode::KB_F,                      "KB_F" },
        { InputCode::KB_G,                      "KB_G" },
        { InputCode::KB_H,                      "KB_H" },
        { InputCode::KB_I,                      "KB_I" },
        { InputCode::KB_J,                      "KB_J" },
        { InputCode::KB_K,                      "KB_K" },
        { InputCode::KB_L,                      "KB_L" },
        { InputCode::KB_M,                      "KB_M" },
        { InputCode::KB_N,                      "KB_N" },
        { InputCode::KB_O,                      "KB_O" },
        { InputCode::KB_P,                      "KB_P" },
        { InputCode::KB_Q,                      "KB_Q" },
        { InputCode::KB_R,                      "KB_R" },
        { InputCode::KB_S,                      "KB_S" },
        { InputCode::KB_T,                      "KB_T" },
        { InputCode::KB_U,                      "KB_U" },
        { InputCode::KB_V,                      "KB_V" },
        { InputCode::KB_W,                      "KB_W" },
        { InputCode::KB_X,                      "KB_X" },
        { InputCode::KB_Y,                      "KB_Y" },
        { InputCode::KB_Z,                      "KB_Z" },
        { InputCode::KB_1,                      "KB_1" },
        { InputCode::KB_2,                      "KB_2" },
        { InputCode::KB_3,                      "KB_3" },
        { InputCode::KB_4,                      "KB_4" },
        { InputCode::KB_5,                      "KB_5" },
        { InputCode::KB_6,                      "KB_6" },
        { InputCode::KB_7,                      "KB_7" },
        { InputCode::KB_8,                      "KB_8" },
        { InputCode::KB_9,                      "KB_9" },
        { InputCode::KB_0,                      "KB_0" },
        { InputCode::KB_RETURN,                 "KB_RETURN" },
        { InputCode::KB_ESC,                    "KB_ESC" },
        { InputCode::KB_BACKSPACE,              "KB_BACKSPACE" },
        { InputCode::KB_TAB,                    "KB_TAB" },
        { InputCode::KB_SPACE,                  "KB_SPACE" },
        { InputCode::KB_RIGHT,                  "KB_RIGHT" },
        { InputCode::KB_LEFT,                   "KB_LEFT" },
        { InputCode::KB_UP,                     "KB_UP" },
        { InputCode::KB_DOWN,                   "KB_DOWN" },
        { InputCode::KB_LCTRL,                  "KB_LCTRL" },
        { InputCode::KB_LSHIFT,                 "KB_LSHIFT" },
        { InputCode::KB_LALT,                   "KB_LALT" },
        { InputCode::KB_RCTRL,                  "KB_RCTRL" },
        { InputCode::KB_RSHIFT,                 "KB_RSHIFT" },
        { InputCode::KB_RALT,                   "KB_RALT" },
        { InputCode::KB_F1,                     "KB_F1" },
        { InputCode::KB_F2,                     "KB_F2" },
        { InputCode::KB_F3,                     "KB_F3" },
        { InputCode::KB_F4,                     "KB_F4" },
        { InputCode::KB_F5,                     "KB_F5" },
        { InputCode::KB_F6,                     "KB_F6" },
        { InputCode::KB_F7,                     "KB_F7" },
        { InputCode::KB_F8,                     "KB_F8" },
        { InputCode::KB_F9,                     "KB_F9" },
        { InputCode::KB_F10,                    "KB_F10" },
        { InputCode::KB_F11,                    "KB_F11" },
        { InputCode::KB_F12,                    "KB_F12" },
        { InputCode::GP_BUTTON_SOUTH,           "GP_BUTTON_SOUTH" },
        { InputCode::GP_BUTTON_EAST,            "GP_BUTTON_EAST" },
        { InputCode::GP_BUTTON_WEST,            "GP_BUTTON_WEST" },
        { InputCode::GP_BUTTON_NORTH,           "GP_BUTTON_NORTH" },
        { InputCode::GP_BUTTON_BACK,            "GP_BUTTON_BACK" },
        { InputCode::GP_BUTTON_GUIDE,           "GP_BUTTON_GUIDE" },
        { InputCode::GP_BUTTON_START,           "GP_BUTTON_START" },
        { InputCode::GP_BUTTON_LEFT_STICK,      "GP_BUTTON_LEFT_STICK" },
        { InputCode::GP_BUTTON_RIGHT_STICK,     "GP_BUTTON_RIGHT_STICK" },
        { InputCode::GP_BUTTON_LEFT_SHOULDER,   "GP_BUTTON_LEFT_SHOULDER" },
        { InputCode::GP_BUTTON_RIGHT_SHOULDER,  "GP_BUTTON_RIGHT_SHOULDER" },
        { InputCode::GP_BUTTON_DPAD_UP,         "GP_BUTTON_DPAD_UP" },
        { InputCode::GP_BUTTON_DPAD_DOWN,       "GP_BUTTON_DPAD_DOWN" },
        { InputCode::GP_BUTTON_DPAD_LEFT,       "GP_BUTTON_DPAD_LEFT" },
        { InputCode::GP_BUTTON_DPAD_RIGHT,      "GP_BUTTON_DPAD_RIGHT" },
        { InputCode::GP_BUTTON_RIGHT_PADDLE1,   "GP_BUTTON_RIGHT_PADDLE1" },
        { InputCode::GP_BUTTON_LEFT_PADDLE1,    "GP_BUTTON_LEFT_PADDLE1" },
        { InputCode::GP_BUTTON_RIGHT_PADDLE2,   "GP_BUTTON_RIGHT_PADDLE2" },
        { InputCode::GP_BUTTON_LEFT_PADDLE2,    "GP_BUTTON_LEFT_PADDLE2" }
    })
}

#endif