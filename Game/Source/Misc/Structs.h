#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <Misc/Enums.h>

namespace Game
{
    struct CreatureInfo final
    {
        int Lives{ 3 };
        int Score{};
    };

    struct MoveInstruction final
    {
        MovementEvent MovementEvent{ MovementEvent::OnIdle };
        Direction Direction{ Direction::UpRight };
    };
}

#endif