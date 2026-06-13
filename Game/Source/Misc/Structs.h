#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <Misc/Enums.h>

namespace Game
{
    struct CreatureInfo final
    {
        PlayerIndex PlayerIndex     { PlayerIndex::None };
        int Lives                   { 1 };
        int Score                   { 0 };
    };

    struct MoveInstruction final
    {
        MovementEvent MovementEvent { MovementEvent::OnIdle };
        Direction Direction         { Direction::UpRight };
    };
}

#endif
