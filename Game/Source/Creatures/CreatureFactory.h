#ifndef CREATURE_FACTORY_H
#define CREATURE_FACTORY_H

#include <Components/BaseCreature.h>
#include <Misc/Enums.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Types.h>

#include <string>
#include <unordered_map>

namespace Game
{
    struct CreatureData
    {
        std::string         SpritePath;
        int                 SpriteRows;
        int                 SpriteCols;
        GameEngine::Pivot   Pivot;
        vec2                PivotOffset;
        BlockSurface        SpawnSurface;
    };

    class CreatureFactory
    {
    private:
        static void BuildCreatureController(Game::Creature creatureType, GameEngine::GameObject& gameObject);

    public:
        static inline std::unordered_map<Creature, CreatureData> const CREATURE_TABLE =
        {
            { Creature::QBert,       { "Qbert.png",    1, 8, GameEngine::Pivot::MiddleDown, {0,0},    BlockSurface::Top     }},
            { Creature::Coily,       { "Coily.png",    1, 8, GameEngine::Pivot::MiddleDown, {0,0},    BlockSurface::Top     }},
            { Creature::GreenSlime,  { "Slimes.png",   1, 6, GameEngine::Pivot::MiddleDown, {0,0},    BlockSurface::Top     }},
            { Creature::RedSlime,    { "Slimes.png",   1, 6, GameEngine::Pivot::MiddleDown, {0,0},    BlockSurface::Top     }},
            { Creature::PurpleSlime, { "Slimes.png",   1, 6, GameEngine::Pivot::MiddleDown, {0,0},    BlockSurface::Top     }},
            { Creature::Ugg,         { "Ugg.png",      1, 8, GameEngine::Pivot::LeftUp,     {2,2},    BlockSurface::Right   }},
            { Creature::WrongWay,    { "Wrongway.png", 1, 8, GameEngine::Pivot::RightUp,    {-2,2},   BlockSurface::Left    }},
        };

        static void BuildCreatureComponents(GameEngine::GameObject& gameObject, Creature creatureType);
    };
}

#endif