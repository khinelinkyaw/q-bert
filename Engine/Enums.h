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
}

#endif