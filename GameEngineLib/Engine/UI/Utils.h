#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <glm/glm.hpp>

#include <Engine/Misc/Structs.h>
#include <Engine/Misc/Constants.h>
#include <Engine/Misc/Enums.h>

namespace GameEngine::UI
{
    glm::vec2 AlignToWindow(Pivot pivot, float hMargin, float vMargin)
    {
        auto [hDir, vDir] { Constants::UI_PIVOT_MAP.at(pivot)};

        float hAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(hDir) };
        float vAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(vDir) };

        float xPos{ static_cast<float>(Constants::WINDOW_WIDTH) * hAlighment };
        float yPos{ static_cast<float>(Constants::WINDOW_HEIGHT) * vAlighment };

        //float xSign{ Constants::UI_DIRECTION_MULTI_MAP.at(hDir) };
        //float ySign{ Constants::UI_DIRECTION_MULTI_MAP.at(vDir) };

        xPos += hMargin;
        yPos += vMargin;

        return glm::vec2{ xPos, yPos};
    }

    glm::vec2 AlignToWindow(float hPercent, float vPercent)
    {
        float xPos{ Constants::WINDOW_WIDTH * hPercent };
        float yPos{ Constants::WINDOW_HEIGHT * vPercent };

        return glm::vec2{ xPos, yPos };
    }

    glm::vec2 AlignToRect(float hOffset, float vOffset, Rect<float> rect, Pivot pivot = Pivot::LeftUp)
    {
        auto [hDir, vDir] { Constants::UI_PIVOT_MAP.at(pivot) };

        float hAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(hDir) };
        float vAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(vDir) };

        float xPos{ (static_cast<float>(rect.width) * hAlighment) + rect.x };
        float yPos{ (static_cast<float>(rect.height) * vAlighment) + rect.y };

        xPos += hOffset;
        yPos += vOffset;

        return glm::vec2{ xPos, yPos };
    }

    glm::vec2 AlignToRect(glm::vec2 offset, Rect<float> rect, Pivot pivot = Pivot::LeftUp)
    {
        auto [hDir, vDir] { Constants::UI_PIVOT_MAP.at(pivot) };

        float hAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(hDir) };
        float vAlighment{ Constants::UI_DIRECTION_OFFSET_MAP.at(vDir) };

        float xPos{ (static_cast<float>(rect.width) * hAlighment) + rect.x };
        float yPos{ (static_cast<float>(rect.height) * vAlighment) + rect.y };

        xPos += offset.x;
        yPos += offset.y;

        return glm::vec2{ xPos, yPos };
    }
}

#endif