#include "CollisionComponent.h"

#include <Engine/Core/GameObject.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Components/TextureComponent.h>

using namespace GameEngine;

Rect<float> GameEngine::CollisionComponent::GetRect() const
{
    auto position{ GetOwnerObject()->GetTransform()->GetWorldPosition() };

    return {
        position.x + m_CollisionRect.x,
        position.y + m_CollisionRect.y,
        m_CollisionRect.width,
        m_CollisionRect.height
    };
}

void CollisionComponent::SetRect(float x, float y, float width, float height)
{
    m_CollisionRect = Rect<float>{ x, y, width, height };
}

void CollisionComponent::SetRect(Rect<float> const& collisionRect)
{
    m_CollisionRect = collisionRect;
}

void CollisionComponent::NotifyOnCollision(GameObject* other)
{
    m_CollisionObserver.OnNotify(*other, "OnCollision");
}

CollisionComponent::CollisionComponent(GameObject* owner)
    : BaseComponent{ owner }
    , m_CollisionObserver{ owner }
{
    auto textureComp{ owner->GetComponent<TextureComponent>() };

    if (textureComp != nullptr)
    {
        SetRect(textureComp->GetSize());
    }
}
