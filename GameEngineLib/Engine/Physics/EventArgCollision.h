#ifndef EVENT_ARG_COLLISION_H
#define EVENT_ARG_COLLISION_H

#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>

namespace GameEngine
{
    struct EventArgCollision final : public EventArg
    {
        GameObject* OtherObject{};
    };
}

#endif