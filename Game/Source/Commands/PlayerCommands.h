#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <Misc/Enums.h>

#include <Engine/Events/EventArg.h>

namespace Game
{
    struct EventArgMove final : public GameEngine::EventArg
    {
        MovementEvent MovementEvent{ MovementEvent::OnIdle };
        Direction Direction{ Direction::UpRight };
    };
}

#endif
