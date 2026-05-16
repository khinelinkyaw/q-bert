#include "CollisionComponent.h"

#include <Engine/Core/GameObject.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Rendering/Renderer.h>

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

void GameEngine::CollisionComponent::Render(glm::vec3 const& pos) const
{
    SDL_FRect collisionRect{ pos.x + m_CollisionRect.x, pos.y + m_CollisionRect.y, m_CollisionRect.width, m_CollisionRect.height };
    Renderer::Get().DrawRect(collisionRect, SDL_Color{ 255, 0, 0, 255 });
}

CollisionComponent::CollisionComponent(GameObject* owner)
    : BaseComponent{ owner }
    , m_CollisionObserver{ owner }
{
    auto textureComp{ owner->GetComponent<TextureComponent>() };

    if (textureComp != nullptr)
    {
        auto textureRect{ textureComp->GetSrcRect() };
        auto origin{ textureComp->GetOrigin() };

        m_CollisionRect = Rect<float>{
            -origin.x,
            -origin.y,
            textureRect.width,
            textureRect.height
        };
    }

    ServiceLocator::Get().GetCollisionSystem().AddCollisionComponent(this);
}

GameEngine::CollisionComponent::~CollisionComponent()
{
    ServiceLocator::Get().GetCollisionSystem().RemoveCollisionComponent(this);
}
