#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

namespace Game
{
    namespace Screen
    {
        int constexpr GAME_WIDTH{ 300 };
        int constexpr GAME_HEIGHT{ 300 };
    }

    namespace Consts
    {
        namespace Enemy
        {
            float constexpr IDLE_DURATION{ 1.f };
            int constexpr   MAX_NORMAL_ENEMY_PATH_SIZE{ 7 };
            int constexpr   MAX_PURPLE_SLIME_PATH_SIZE{ 5 };
        };
    }
}

#endif