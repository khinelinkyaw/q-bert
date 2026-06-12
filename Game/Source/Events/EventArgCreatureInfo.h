#ifndef EVENT_ARG_CREATURE_INFO_H
#define EVENT_ARG_CREATURE_INFO_H

#include <Engine/Events/EventArg.h>
#include <Misc/Structs.h>

namespace Game
{
    struct EventArgCreatureInfo final : public GameEngine::EventArg
    {
        CreatureInfo CreatureInfo{};
    };
}

#endif