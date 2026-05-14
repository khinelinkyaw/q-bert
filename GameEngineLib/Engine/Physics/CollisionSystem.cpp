#include "CollisionSystem.h"

#include <Engine/Physics/Utils.h>

using namespace GameEngine;

void CollisionSystem::CheckCollisions()
{
    for (auto eachComponent : m_CollisionComponents)
    {
        for (auto otherComponent : m_CollisionComponents)
        {
            if (eachComponent == otherComponent) return;

            if (Collision::CollisionBetweenRects<float>(eachComponent->GetRect(), otherComponent->GetRect()))
            {
                eachComponent->NotifyOnCollision(otherComponent->GetOwnerObject());
                otherComponent->NotifyOnCollision(eachComponent->GetOwnerObject());
            }
        }
    }
}
