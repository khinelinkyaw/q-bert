#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

namespace Game
{
    using json = nlohmann::json;

    enum class UIType
    {
        Empty,
        Texture,
        Sprite,
        AnimatedSprite,
        SpriteFont
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(UIType,
    {
        { UIType::Empty,          "Empty"},
        { UIType::Texture,        "Texture"},
        { UIType::Sprite,         "Sprite"         },
        { UIType::AnimatedSprite, "AnimatedSprite" },
        { UIType::SpriteFont,     "SpriteFont" }
    })

    enum class Gamemode
    {
        Solo = 0,
        Coop = 1,
        Versus = 2
    };

    enum class PlayerIndex
    {
        None,
        Player1,
        Player2
    };

    enum class BlockSurface
    {
        Top,
        Left,
        Right
    };

    enum class BlockColor
    {
        Empty       = -1,
        Yellow      = 0,
        Magenta     = 1,
        Red         = 2,
        Sand        = 3,
        BrightBlue  = 4,
        Green       = 5,
        LightGray   = 6,
        DarkGray    = 7,
        Blue        = 8
    };

    enum class Direction
    {
        UpRight = 0,
        UpLeft = 1,
        DownRight = 2,
        DownMiddle = 3,
        DownLeft = 4,
        LevelRight = 5,
        LevelLeft = 6,
    };

    enum class MovementEvent
    {
        OnIdle = 00,
        OnIdleWait = 00,
        OnHop = 10,
        OnDeath = 20,
        OnVictory = 30,
    };

    enum class Creature
    {
        QBert,
        RedSlime,
        GreenSlime,
        PurpleSlime,
        Coily,
        Ugg,
        WrongWay,
        Slick,
        Sam
    };
}

#endif