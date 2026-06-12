#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Types.h>

#include <vector>

namespace GameEngine
{
    class GameObject;

    class TransformComponent final : public BaseComponent
    {
    private:
        std::vector<GameObject*> m_ChildObjs;
        vec2 m_LocalPosition;
        mutable vec2 m_WorldPosition;
        float m_ZIndex{ 0.f };
        GameObject* m_ParentObj;
        mutable bool m_DirtyFlag;
        
        void SetDirtyFlagRecursively();
        void UpdateWorldPosition() const;
        void AddChild(GameObject* childObj);
        void RemoveChild(GameObject* childObj);

    public:
#pragma region BaseComponentFunctions
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
#pragma endregion

        vec2 GetLocalPosition() const;
        void SetLocalPosition(vec2 newPos);
        //void SetLocalPosition(vec3 newPos) = delete;
        void SetLocalPosition(float x, float y);
        void SetLocalX(float x);
        void SetLocalY(float y);

        void SetWorldPosition(vec2 worldPosition);
        void SetWorldX(float x);
        void SetWorldY(float y);

        void SetZIndex(float z);

        vec2 GetWorldPosition() const;
        float GetZIndex() const;

        void SetParent(GameObject* newParentObjarentObj);

        TransformComponent(GameObject* owner);
        ~TransformComponent() = default;
    };
}

#endif
