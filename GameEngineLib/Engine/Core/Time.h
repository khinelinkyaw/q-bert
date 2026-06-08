#ifndef MINIGIN_TIME_H
#define MINIGIN_TIME_H

namespace GameEngine
{
    namespace EngineUse
    {
        void SetDeltaTime(float deltaTime);
    }
    float GetDeltaTime();
    float GetFixedTime();
}

#endif