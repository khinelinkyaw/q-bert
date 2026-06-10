#ifndef CREATURES_SPRITE_MAPS_H
#define CREATURES_SPRITE_MAPS_H

#include <Misc/Enums.h>

#include <unordered_map>

namespace Game
{
    namespace Sprites
    {
        std::unordered_map<int, int> const QBERT_SPRITE_MAP{
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     0 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      1 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      2 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       3 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   4 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    5 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    6 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     7 },
        };

        std::unordered_map<int, int> const RED_SLIME_SPRITE_MAP{
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     0 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      1 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      0 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       1 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   0 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    1 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    0 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     1 },
        };

        std::unordered_map<int, int> const GREEN_SLIME_SPRITE_MAP{
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     2 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      3 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      2 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       3 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   2 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    3 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    2 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     3 },
        };

        std::unordered_map<int, int> const PURPLE_SLIME_SPRITE_MAP{
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     4 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      5 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      4 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       5 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   4 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    5 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    4 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     5 },
        };

        std::unordered_map<int, int> const COILY_SPRITE_MAP{
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     0 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      1 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      2 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       3 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   4 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    5 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    6 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     7 },
        };

        std::unordered_map<int, int> const UGG_SPRITE_MAP{
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnIdle),      0 },
            {static_cast<int>(Direction::UpLeft) + static_cast<int>(MovementEvent::OnHop),       1 },
            {static_cast<int>(Direction::LevelLeft) + static_cast<int>(MovementEvent::OnIdle),    4 },
            {static_cast<int>(Direction::LevelLeft) + static_cast<int>(MovementEvent::OnHop),     5 },
        };

        std::unordered_map<int, int> const WRONGWAY_SPRITE_MAP{
            {static_cast<int>(Direction::LevelRight) + static_cast<int>(MovementEvent::OnIdle),   0 },
            {static_cast<int>(Direction::LevelRight) + static_cast<int>(MovementEvent::OnHop),    1 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnIdle),     4 },
            {static_cast<int>(Direction::UpRight) + static_cast<int>(MovementEvent::OnHop),      5 },
        };

        std::unordered_map<int, int> const SLICK_SPRITE_MAP{
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    0 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     1 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   4 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    5 },
        };

        std::unordered_map<int, int> const SAM_SPRITE_MAP{
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnIdle),    0 },
            {static_cast<int>(Direction::DownLeft) + static_cast<int>(MovementEvent::OnHop),     1 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnIdle),   4 },
            {static_cast<int>(Direction::DownRight) + static_cast<int>(MovementEvent::OnHop),    5 },
        };

        std::unordered_map<Creature, std::unordered_map<int, int> const*> const CREATURE_SPRITE_MAP{
            { Creature::QBert,       &QBERT_SPRITE_MAP },
            { Creature::RedSlime,    &RED_SLIME_SPRITE_MAP },
            { Creature::GreenSlime,  &GREEN_SLIME_SPRITE_MAP },
            { Creature::PurpleSlime, &PURPLE_SLIME_SPRITE_MAP },
            { Creature::Coily,       &COILY_SPRITE_MAP },
            { Creature::Ugg,         &UGG_SPRITE_MAP },
            { Creature::WrongWay,    &WRONGWAY_SPRITE_MAP },
            { Creature::Slick,       &SLICK_SPRITE_MAP },
            { Creature::Sam,         &SAM_SPRITE_MAP },
        };
    }
}

#endif