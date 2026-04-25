#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Engine/Misc/Enums.h>
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

        //std::unordered_map<Direction, float> const UI_DIRECTION_MULTI_MAP{
        //    { Direction::Up, 1.0f },
        //    { Direction::Level, 0.0f },
        //    { Direction::Down, -1.f },
        //    { Direction::Left, 1.f },
        //    { Direction::Middle, 0.0f },
        //    { Direction::Right, -1.f }
        //};

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
    }
}

#endif