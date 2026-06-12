#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Engine/Misc/Enums.h>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>

#include <unordered_map>
#include <utility>

namespace GameEngine
{
    namespace Constants
    {
        int constexpr WINDOW_WIDTH{ 1024 };
        int constexpr WINDOW_HEIGHT{ 576 };

        std::unordered_map<Direction, float> const UI_DIRECTION_OFFSET_MAP{
            { Direction::Up, 0.0f },
            { Direction::Level, 0.5f },
            { Direction::Down, 1.f },
            { Direction::Left, 0.f },
            { Direction::Middle, 0.5f },
            { Direction::Right, 1.f }
        };

        std::unordered_map<Direction, float> const UI_DIRECTION_MULTI_MAP{
            { Direction::Up, 1.0f },
            { Direction::Level, 1.0f },
            { Direction::Down, -1.f },
            { Direction::Left, 1.f },
            { Direction::Middle, 1.0f },
            { Direction::Right, -1.f }
        };

        // Where is the origin?
        // Top left is the origin (0,0)

        std::unordered_map<Pivot, std::pair<Direction, Direction>> const UI_PIVOT_MAP {
            { Pivot::LeftUp,        {Direction::Left, Direction::Up} },
            { Pivot::LeftLevel,     {Direction::Left, Direction::Level} },
            { Pivot::LeftDown,      {Direction::Left, Direction::Down} },
            { Pivot::MiddleUp,      {Direction::Middle, Direction::Up} },
            { Pivot::MiddleLevel,   {Direction::Middle, Direction::Level} },
            { Pivot::MiddleDown,    {Direction::Middle, Direction::Down} },
            { Pivot::RightUp,       {Direction::Right, Direction::Up} },
            { Pivot::RightLevel,    {Direction::Right, Direction::Level} },
            { Pivot::RightDown,     {Direction::Right, Direction::Down} }
        };

        int constexpr MAX_CONTROLLER_COUNT{ 4 };

        std::unordered_map<InputCode, int> const INPUT_CODE_MAP{
            {InputCode::KB_A, SDL_SCANCODE_A},
            {InputCode::KB_B, SDL_SCANCODE_B},
            {InputCode::KB_C, SDL_SCANCODE_C},
            {InputCode::KB_D, SDL_SCANCODE_D},
            {InputCode::KB_E, SDL_SCANCODE_E},
            {InputCode::KB_F, SDL_SCANCODE_F},
            {InputCode::KB_G, SDL_SCANCODE_G},
            {InputCode::KB_H, SDL_SCANCODE_H},
            {InputCode::KB_I, SDL_SCANCODE_I},
            {InputCode::KB_J, SDL_SCANCODE_J},
            {InputCode::KB_K, SDL_SCANCODE_K},
            {InputCode::KB_L, SDL_SCANCODE_L},
            {InputCode::KB_M, SDL_SCANCODE_M},
            {InputCode::KB_N, SDL_SCANCODE_N},
            {InputCode::KB_O, SDL_SCANCODE_O},
            {InputCode::KB_P, SDL_SCANCODE_P},
            {InputCode::KB_Q, SDL_SCANCODE_Q},
            {InputCode::KB_R, SDL_SCANCODE_R},
            {InputCode::KB_S, SDL_SCANCODE_S},
            {InputCode::KB_T, SDL_SCANCODE_T},
            {InputCode::KB_U, SDL_SCANCODE_U},
            {InputCode::KB_V, SDL_SCANCODE_V},
            {InputCode::KB_W, SDL_SCANCODE_W},
            {InputCode::KB_X, SDL_SCANCODE_X},
            {InputCode::KB_Y, SDL_SCANCODE_Y},
            {InputCode::KB_Z, SDL_SCANCODE_Z},
            {InputCode::KB_1, SDL_SCANCODE_1},
            {InputCode::KB_2, SDL_SCANCODE_2},
            {InputCode::KB_3, SDL_SCANCODE_3},
            {InputCode::KB_4, SDL_SCANCODE_4},
            {InputCode::KB_5, SDL_SCANCODE_5},
            {InputCode::KB_6, SDL_SCANCODE_6},
            {InputCode::KB_7, SDL_SCANCODE_7},
            {InputCode::KB_8, SDL_SCANCODE_8},
            {InputCode::KB_9, SDL_SCANCODE_9},
            {InputCode::KB_0, SDL_SCANCODE_0},
            {InputCode::KB_RETURN, SDL_SCANCODE_RETURN},
            {InputCode::KB_ESC, SDL_SCANCODE_ESCAPE},
            {InputCode::KB_BACKSPACE, SDL_SCANCODE_BACKSPACE},
            {InputCode::KB_TAB, SDL_SCANCODE_TAB},
            {InputCode::KB_SPACE, SDL_SCANCODE_SPACE},
            {InputCode::KB_RIGHT, SDL_SCANCODE_RIGHT},
            {InputCode::KB_LEFT, SDL_SCANCODE_LEFT},
            {InputCode::KB_UP, SDL_SCANCODE_UP},
            {InputCode::KB_DOWN, SDL_SCANCODE_DOWN},
            {InputCode::KB_LCTRL, SDL_SCANCODE_LCTRL},
            {InputCode::KB_LSHIFT, SDL_SCANCODE_LSHIFT},
            {InputCode::KB_LALT, SDL_SCANCODE_LALT},
            {InputCode::KB_RCTRL, SDL_SCANCODE_RCTRL},
            {InputCode::KB_RSHIFT, SDL_SCANCODE_RSHIFT},
            {InputCode::KB_RALT, SDL_SCANCODE_RALT},

            {InputCode::GP_BUTTON_SOUTH, SDL_GAMEPAD_BUTTON_SOUTH},
            {InputCode::GP_BUTTON_EAST, SDL_GAMEPAD_BUTTON_EAST},
            {InputCode::GP_BUTTON_WEST, SDL_GAMEPAD_BUTTON_WEST},
            {InputCode::GP_BUTTON_NORTH, SDL_GAMEPAD_BUTTON_NORTH},
            {InputCode::GP_BUTTON_BACK, SDL_GAMEPAD_BUTTON_BACK},
            {InputCode::GP_BUTTON_GUIDE, SDL_GAMEPAD_BUTTON_GUIDE},
            {InputCode::GP_BUTTON_START, SDL_GAMEPAD_BUTTON_START},
            {InputCode::GP_BUTTON_LEFT_STICK, SDL_GAMEPAD_BUTTON_LEFT_STICK},
            {InputCode::GP_BUTTON_RIGHT_STICK, SDL_GAMEPAD_BUTTON_RIGHT_STICK},
            {InputCode::GP_BUTTON_LEFT_SHOULDER, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
            {InputCode::GP_BUTTON_RIGHT_SHOULDER, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
            {InputCode::GP_BUTTON_DPAD_UP, SDL_GAMEPAD_BUTTON_DPAD_UP},
            {InputCode::GP_BUTTON_DPAD_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN},
            {InputCode::GP_BUTTON_DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT},
            {InputCode::GP_BUTTON_DPAD_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
            {InputCode::GP_BUTTON_RIGHT_PADDLE1, SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1},
            {InputCode::GP_BUTTON_LEFT_PADDLE1, SDL_GAMEPAD_BUTTON_LEFT_PADDLE1},
            {InputCode::GP_BUTTON_RIGHT_PADDLE2, SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2},
            {InputCode::GP_BUTTON_LEFT_PADDLE2, SDL_GAMEPAD_BUTTON_LEFT_PADDLE2}
        };
    }
}

#endif