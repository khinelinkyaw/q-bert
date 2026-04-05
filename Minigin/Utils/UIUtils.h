#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <glm/glm.hpp>
#include <unordered_map>
#include <array>

namespace GameEngine
{
    enum class Direction
    {
        Up,
        Left,
        Down,
        Right
    };

    enum class Corner
    {
        UpLeft,
        UpRight,
        DownLeft,
        DownRight
    };

    namespace Constants
    {
        std::unordered_map<Corner, std::array<Direction, 2>> const UI_CORNER_MAP{
            { Corner::UpLeft,    {Direction::Up, Direction::Left} },
            { Corner::UpRight,   {Direction::Up, Direction::Right} },
            { Corner::DownLeft,  {Direction::Down, Direction::Left} },
            { Corner::DownRight, {Direction::Down, Direction::Right} }
        };

        std::unordered_map<Direction, int> const UI_DIRECTION_MAP{
            { Direction::Up, 1 },
            { Direction::Left, -1 },
            { Direction::Down, 1 },
            { Direction::Right, 1 }
        };
    }


}

#endif