#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <Characters/MovementState.h>

#include <Engine/Decoupling/Event.h>

namespace Game
{
    struct EventArgMove final : public GameEngine::EventArg
    {
        MovementEvent MovementEvent{ MovementEvent::OnIdle };
        LookDirection Direction{ LookDirection::UpRight };
    };
}

#endif
