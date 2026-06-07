#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

namespace Game
{
    enum class BlockSurface
    {
        Top,
        Left,
        Right
    };

    enum class BlockType
    {
        Green,
        Blue,
        Magenta,
        Empty
    };

    enum class Direction
    {
        UpRight = 0,
        UpLeft = 1,
        DownRight = 2,
        DownLeft = 3,
        LevelRight = 4,
        LevelLeft = 5,
    };

    enum class MovementEvent
    {
        OnIdle = 00,
        OnIdleWait = 00,
        OnHop = 10,
        OnDeath = 20,
        OnVictory = 30,
    };
}

#endif