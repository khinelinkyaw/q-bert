#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <Events/EventArgMove.h>

#include <memory>
#include <queue>

namespace Game
{
    using MovePath = std::queue<std::unique_ptr<EventArgMove>>;
}

#endif