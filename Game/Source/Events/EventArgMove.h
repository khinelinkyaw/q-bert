#ifndef EVENT_ARG_MOVE_H
#define EVENT_ARG_MOVE_H

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
