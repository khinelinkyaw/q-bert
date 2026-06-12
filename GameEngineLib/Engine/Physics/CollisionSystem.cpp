#include "CollisionSystem.h"

#include <Engine/Components/CollisionComponent.h>
#include <Engine/Physics/Utils.h>

#include <algorithm>
#include <utility>
#include <vector>

using namespace GameEngine;

void CollisionSystem::CheckCollisions()
{
    for (auto eachComponent : m_CollisionComponents)
    {
        std::vector<CollisionComponent*> newCollisions{};

        for (auto otherComponent : m_CollisionComponents)
        {
            if (eachComponent == otherComponent) continue;

            if (Collision::CollisionBetweenRects<float>(eachComponent->GetRect(), otherComponent->GetRect()))
            {
                newCollisions.push_back(otherComponent);
            }
        }

        eachComponent->CheckCollisions(std::move(newCollisions));
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
