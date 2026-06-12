#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <Engine/Components/CollisionComponent.h>

#include <list>

namespace GameEngine
{
    class CollisionSystem final
    {
    private:
        std::list<CollisionComponent*> m_CollisionComponents{};

    public:
        void CheckCollisions();
        void AddCollisionComponent(CollisionComponent* collisionComponent) { m_CollisionComponents.push_back(collisionComponent); }
        void RemoveCollisionComponent(CollisionComponent* collisionComponent);
    };
}

#endif
