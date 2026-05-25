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
        vec3 m_LocalPosition;
        mutable vec3 m_WorldPosition;
        GameObject* m_ParentObj;
        std::vector<GameObject*> m_ChildObjs;
        mutable bool m_DirtyFlag;
        
        void SetDirtyFlagRecursively();
        void UpdateWorldPosition() const;
        void AddChild(GameObject* childObj);
        void RemoveChild(GameObject* childObj);

    public:
#pragma region BaseComponentFunctions
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec3 const&) const override {};
#pragma endregion

        vec3 GetLocalPosition() const;
        void SetLocalPosition(vec3 newPos);
        void SetLocalPosition(float x, float y);
        void SetX(float x);
        void SetY(float y);

        vec3 GetWorldPosition() const;

        void SetParent(GameObject* newParentObjarentObj);

        TransformComponent(GameObject* owner);
        ~TransformComponent() = default;
    };
}

#endif
