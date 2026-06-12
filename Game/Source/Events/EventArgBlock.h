#ifndef EVENT_ARG_BLOCK_H
#define EVENT_ARG_BLOCK_H

#include <Engine/Events/EventArg.h>

namespace Game
{
    class Block;
    struct EventArgBlock final : public GameEngine::EventArg
    {
        Block* Block;
    };
}

#endif