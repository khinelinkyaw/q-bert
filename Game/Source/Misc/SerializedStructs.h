#ifndef SERIALIZED_STRUCTS_H
#define SERIALIZED_STRUCTS_H

#include <Misc/Enums.h>

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace Game
{
    struct CreatureSpawnerInfo final
    {
        Creature CreatureType{};
        float SpawnInterval{ 5.f };
        int SpawnProbability{ 100 };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CreatureSpawnerInfo,
        CreatureType,
        SpawnInterval,
        SpawnProbability
    )

    struct RoundInfo final
    {
        BlockColor                       StartingBlockColor{};
        BlockColor                       FinalBlockColor{};
        std::vector<CreatureSpawnerInfo> CreatureSpawnersInfo{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(RoundInfo,
        StartingBlockColor,
        FinalBlockColor,
        CreatureSpawnersInfo
    )

    struct LevelInfo final
    {
        bool CycleBackBlocks{ false };
        std::vector<RoundInfo> RoundsInfo{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LevelInfo,
        CycleBackBlocks,
        RoundsInfo
    )

    struct GameplayInfo final
    {
        std::string            UIJSONPath{ "" };
        std::vector<LevelInfo> LevelsInfo{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(GameplayInfo,
        UIJSONPath,
        LevelsInfo
    )
}

#endif
