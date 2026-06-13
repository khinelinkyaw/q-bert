#ifndef GAME_ENGINE_SERIALIZED_STRUCTS_H
#define GAME_ENGINE_SERIALIZED_STRUCTS_H

#include <Engine/Misc/Enums.h>

#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>

namespace GameEngine
{
    using json = nlohmann::json;

    struct SimpleVector2 final
    {
        float x{ 0.f };
        float y{ 0.f };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(SimpleVector2, x, y)

        struct UIComponentInfo final
    {
        UIType                      Type{ UIType::Empty };
        std::string                 TextureFilePath{};
        SimpleVector2               ContainerSize{ 0.f, 0.f };
        int                         SpriteIndex{};
        int                         SpriteRows{};
        int                         SpriteCols{};
        std::string                 Text{ "0" };
        std::vector<int>            AnimationFrameIndices{};
        GameEngine::AnimationType   AnimationType{ GameEngine::AnimationType::Loop };
        float                       AnimationDuration{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UIComponentInfo,
        Type,
        TextureFilePath,
        ContainerSize,
        SpriteIndex,
        SpriteRows,
        SpriteCols,
        Text,
        AnimationFrameIndices,
        AnimationType,
        AnimationDuration
    )

        struct UIPositioningInfo final
    {
        std::string                 ParentName{};
        SimpleVector2               PaddingSize{ 0.f, 0.f };
        GameEngine::Pivot           PivotOnParent{ GameEngine::Pivot::LeftUp };
        GameEngine::Pivot           Pivot{ GameEngine::Pivot::LeftUp };
        bool                        FixedPadding{ false };
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UIPositioningInfo,
        ParentName,
        PaddingSize,
        PivotOnParent,
        Pivot,
        FixedPadding)

        struct UIElementInfo final
    {
        UIComponentInfo             ComponentInfo{};
        UIPositioningInfo           PositioningInfo{};
        std::string                 Name{};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UIElementInfo,
        ComponentInfo,
        PositioningInfo,
        Name)
}

#endif
