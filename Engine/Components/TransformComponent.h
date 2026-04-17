#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <Engine/Components/BaseComponent.h>

#include <glm/glm.hpp>
#include <vector>

namespace GameEngine
{
    using vector3 = glm::vec3;

    class GameObject;

    class TransformComponent final : public BaseComponent
    {
    private:
        vector3 m_LocalPosition;
        mutable vector3 m_WorldPosition;
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
        void Render(vector3 const&) const {};
#pragma endregion

        vector3 GetLocalPosition() const;
        void SetLocalPosition(vector3 newPos);
        void SetX(float x);
        void SetY(float y);

        vector3 GetWorldPosition() const;

        void SetParent(GameObject* newParentObjarentObj);

        TransformComponent(GameObject* owner);
        ~TransformComponent() = default;
    };
}

#endif
