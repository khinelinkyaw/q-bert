#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <glm/glm.hpp>
#include <Constants.h>
#include <Enums.h>

namespace GameEngine
{
    using glm::vec3;

    constexpr vec3 Align(Pivot pivot, float hMargin, float vMargin)
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

        return vec3{ xPos, yPos, 0.f };
    }

    constexpr vec3 Align(float hPercent, float vPercent)
    {
        float xPos{ Constants::WINDOW_WIDTH * hPercent };
        float yPos{ Constants::WINDOW_HEIGHT * vPercent };

        return vec3{ xPos, yPos, 0.f };
    }
}

#endif