#include "CollisionSystem.h"
#include "CollisionSystem.h"

#include <Engine/Physics/Utils.h>

using namespace GameEngine;

void CollisionSystem::CheckCollisions()
{
    for (auto eachComponent : m_CollisionComponents)
    {
        for (auto otherComponent : m_CollisionComponents)
        {
            if (eachComponent == otherComponent) continue;

            if (Collision::CollisionBetweenRects<float>(eachComponent->GetRect(), otherComponent->GetRect()))
            {
                eachComponent->NotifyOnCollision(otherComponent->GetOwnerObject());
                otherComponent->NotifyOnCollision(eachComponent->GetOwnerObject());
            }
        }
    }
}

void GameEngine::CollisionSystem::RemoveCollisionComponent(CollisionComponent* collisionComponent)
{
    auto it{ std::ranges::find(m_CollisionComponents, collisionComponent) };

    if (it != m_CollisionComponents.end())
    {
        m_CollisionComponents.erase(it);
    }
}
