#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Physics/CollisionObserver.h>

namespace GameEngine
{
    class CollisionComponent final : public BaseComponent
    {
    private:
        Rect<float> m_CollisionRect{};
        CollisionObserver m_CollisionObserver{ nullptr };
        bool m_Active{ true };

    public:
        Rect<float> GetRect() const;
        void SetRect(float x, float y, float width, float height);
        void SetRect(Rect<float> const& collisionRect);
        void SetActive(bool active) { m_Active = active; }

        void NotifyOnCollision(GameObject* other);

        void FixedUpdate() override {};
        void Update() override {};
        void Render(glm::vec3 const&) const override {};

        CollisionComponent(GameObject* owner);
        ~CollisionComponent() override = default;
    };
}

#endif