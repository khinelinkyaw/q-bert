#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <Misc/Enums.h>

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

namespace Game
{
    using json = nlohmann::json;

    struct CreatureInfo final
    {
        PlayerIndex PlayerIndex     { PlayerIndex::None };
        int Lives                   { 3 };
        int Score                   { 0 };
    };

    struct MoveInstruction final
    {
        MovementEvent MovementEvent { MovementEvent::OnIdle };
        Direction Direction         { Direction::UpRight };
    };

    struct SimpleVector2 final
    {
        float x{ 0.f };
        float y{ 0.f };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SimpleVector2, x, y)
}

#endif