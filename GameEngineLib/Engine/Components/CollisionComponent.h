#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <vector>

namespace GameEngine
{
    class GameObject;
    class TextureComponent;
    class CollisionComponent final : public BaseComponent
    {
    private:
        std::vector<CollisionComponent*> m_CollidingComponents{};

        Rect<float> m_CollisionRect{};
        bool m_FollowTexture{ true };
        bool m_Active{ true };

    public:
        Rect<float> GetRect() const;
        void SetRect(float x, float y, float width, float height);
        void SetRect(Rect<float> const& collisionRect);
        void SetActive(bool active) { m_Active = active; }

        void CheckCollisions(std::vector<CollisionComponent*>&& otherComponents);

        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& pos) const override;
        void OnEvent(EventArg* eventArg);

        void ExtractTextureRect(TextureComponent* textureComp);

        CollisionComponent(GameObject* owner);
        ~CollisionComponent() override;
    };
}

#endif