#ifndef EVENT_ARG_INT_H
#define EVENT_ARG_INT_H

#include <Engine/Events/EventArg.h>

namespace GameEngine
{
    struct EventArgInt final : public EventArg
    {
        int Value;
    };
}

#endif
