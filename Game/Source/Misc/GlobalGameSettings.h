#ifndef GLOBAL_GAME_SETTINGS_H
#define GLOBAL_GAME_SETTINGS_H

#include <Misc/Enums.h>

namespace Game
{
    namespace GlobalGameSettings
    {
        inline Gamemode SelectedGamemode{ Gamemode::Solo };
        inline bool IsSoundMuted{ false };
    }
}

#endif