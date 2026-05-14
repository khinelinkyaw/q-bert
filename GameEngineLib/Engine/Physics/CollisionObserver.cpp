#include "CollisionObserver.h"

#include <Engine/Core/GameObject.h>

#include <string>

using namespace GameEngine;

void CollisionObserver::OnNotify(GameObject& gameObject, std::string)
{
    auto components = m_pOwner->GetAllComponents();

    for (auto component : components)
    {
        component->OnCollision(&gameObject);
    }
}

GameEngine::CollisionObserver::CollisionObserver(GameObject* owner)
    : m_pOwner{ owner }
{
}
