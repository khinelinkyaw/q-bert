#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "Enums.h"

#include <unordered_map>

namespace Game
{
    namespace Consts
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

        namespace Enemy
        {
            float constexpr IDLE_DURATION{ 1.f };
            int constexpr   MAX_NORMAL_ENEMY_PATH_SIZE{ 7 };
            int constexpr   MAX_PURPLE_SLIME_PATH_SIZE{ 5 };
        };
    }
}

#endif