#ifndef EVENT_ARG_LEVEL_H
#define EVENT_ARG_LEVEL_H

#include <Misc/Enums.h>

#include <Engine/Events/EventArg.h>

namespace Game
{
    struct EventArgLevel final : public GameEngine::EventArg
    {
        BlockColor FinalBlockColor{};
        int LevelIndex{ 0 };
        int RoundIndex{ 0 };
    };
}

#endif
