#include "CollisionComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Renderer.h>

#include <algorithm>
#include <memory>

using namespace GameEngine;

Rect<float> GameEngine::CollisionComponent::GetRect() const
{
    auto position{ GetOwner()->GetTransform()->GetWorldPosition() };

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

void GameEngine::CollisionComponent::CheckCollisions(std::vector<CollisionComponent*> const& newCollisions)
{
    for (auto const& component : newCollisions)
    {
        auto iter{ std::ranges::find(m_CollidingComponents, component) };

        if (iter == m_CollidingComponents.end())
        {
            GetOwner()->SendEvent(std::make_unique<EventArgCollision>(EventArgCollision{ "OnCollisionEnter", component->GetOwner() }));
        }
        else
        {
            GetOwner()->SendEvent(std::make_unique<EventArgCollision>(EventArgCollision{ "OnCollisionStay", component->GetOwner() }));
        }
    }

    for (auto const& component : m_CollidingComponents)
    {
        auto iter{ std::ranges::find(newCollisions, component) };

        if (iter == newCollisions.end())
        {
            GetOwner()->SendEvent(std::make_unique<EventArgCollision>(EventArgCollision{ "OnCollisionExit", component->GetOwner() }));
        }
    }

    m_CollidingComponents = newCollisions;
}

void GameEngine::CollisionComponent::Render(glm::vec3 const& pos) const
{
    SDL_FRect collisionRect{ pos.x + m_CollisionRect.x, pos.y + m_CollisionRect.y, m_CollisionRect.width, m_CollisionRect.height };
    Renderer::Get().DrawRect(collisionRect, SDL_Color{ 255, 0, 0, 255 });
}

CollisionComponent::CollisionComponent(GameObject* owner)
    : BaseComponent{ owner }
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
