#ifndef MINIGIN_TIME_H
#define MINIGIN_TIME_H

namespace GameEngine
{
    namespace EngineUseOnly
    {
        void SetDeltaTime(float deltaTime);
    }
    float GetDeltaTime();
    float GetFixedTime();
}

#endif