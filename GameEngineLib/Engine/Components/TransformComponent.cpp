#include "TransformComponent.h"
#include <Engine/Misc/GameObject.h>
#include <algorithm>

namespace GameEngine
{
    void TransformComponent::SetDirtyFlagRecursively()
    {
        m_DirtyFlag = true;

        for (auto childObj : m_ChildObjs)
        {
            childObj->GetTransform()->SetDirtyFlagRecursively();
        }
    }

    vector3 TransformComponent::GetLocalPosition() const
    {
        return m_LocalPosition;
    }

    void TransformComponent::SetLocalPosition(vector3 newPos)
    {
        m_LocalPosition = newPos;
        SetDirtyFlagRecursively();
    }

    void TransformComponent::SetX(float x)
    {
        m_LocalPosition.x = x;
        SetDirtyFlagRecursively();
    }

    void TransformComponent::SetY(float y)
    {
        m_LocalPosition.y = y;
        SetDirtyFlagRecursively();
    }

    vector3 TransformComponent::GetWorldPosition() const
    {
        UpdateWorldPosition();
        return m_WorldPosition;
    }

    void TransformComponent::SetParent(GameObject* newParentObj)
    {
        if (newParentObj == GetOwnerObject() or std::ranges::find(m_ChildObjs, newParentObj) != m_ChildObjs.end() or m_ParentObj == newParentObj)
        {
            return;
        }

        if (newParentObj == nullptr)
        {
            SetLocalPosition(GetWorldPosition());
        }
        else
        {
            SetDirtyFlagRecursively();
        }

        if (m_ParentObj)
            m_ParentObj->GetTransform()->RemoveChild(GetOwnerObject());

        m_ParentObj = newParentObj;

        if (m_ParentObj)
            m_ParentObj->GetTransform()->AddChild(GetOwnerObject());
    }

    void TransformComponent::AddChild(GameObject* childObj)
    {
        // ONLY TO BE CALLED BY SetParent
        m_ChildObjs.push_back(childObj);
    }

    void TransformComponent::RemoveChild(GameObject* childObj)
    {
        // ONLY TO BE CALLED BY SetParent
        auto childIter{ std::ranges::find(m_ChildObjs, childObj) };

        if (childIter != m_ChildObjs.end())
        {
            m_ChildObjs.erase(childIter);
        }
    }

    void TransformComponent::UpdateWorldPosition() const
    {
        if (m_DirtyFlag)
        {
            if (m_ParentObj == nullptr)
            {
                m_WorldPosition = GetLocalPosition();
            }
            else
            {
                m_WorldPosition = m_ParentObj->GetTransform()->GetWorldPosition() + GetLocalPosition();
            }
            m_DirtyFlag = false;
        }
    }

    TransformComponent::TransformComponent(GameObject* owner)
        : BaseComponent{owner}
        , m_LocalPosition{}
        , m_WorldPosition{}
        , m_ParentObj{nullptr}
        , m_ChildObjs{}
        , m_DirtyFlag{true}
    {
        GetWorldPosition();
    }
}
