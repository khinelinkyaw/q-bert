#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <Engine/Components/CollisionComponent.h>

#include <vector>

namespace GameEngine
{
    class CollisionSystem final
    {
    private:
        std::vector<CollisionComponent*> m_CollisionComponents{};

    public:
        void CheckCollisions();
    };
}

#endif COLLISION_SYSTEM_H