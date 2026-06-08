#include "Time.h"

namespace GameEngine
{
    namespace GameTime
    {
        static float DeltaTime{ 0.f };
        static float constexpr FixedTime{ 1.f / 60.f };
    }

    namespace EngineUse
    {
        void SetDeltaTime(float deltaTime)
        {
            GameTime::DeltaTime = deltaTime;
        }
    }

    float GetDeltaTime()
    {
        return GameTime::DeltaTime;
    }
    float GetFixedTime()
    {
        return GameTime::FixedTime;
    }
}