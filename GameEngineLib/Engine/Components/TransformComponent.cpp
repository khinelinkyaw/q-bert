#include <Engine/Components/TransformComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

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

    vec2 TransformComponent::GetLocalPosition() const
    {
        return m_LocalPosition;
    }

    void TransformComponent::SetLocalPosition(vec2 newPos)
    {
        SetLocalPosition(newPos.x, newPos.y);
    }

    void TransformComponent::SetLocalPosition(float x, float y)
    {
        m_LocalPosition.x = x;
        m_LocalPosition.y = y;
        SetDirtyFlagRecursively();
    }

    void TransformComponent::SetLocalX(float x)
    {
        SetLocalPosition(x, m_LocalPosition.y);
    }

    void TransformComponent::SetLocalY(float y)
    {
        SetLocalPosition(m_LocalPosition.x, y);
    }

    void TransformComponent::SetWorldPosition(vec2 worldPosition)
    {
        if (m_ParentObj)
        {
            auto parentPosition{ m_ParentObj->GetTransform()->GetWorldPosition() };
            SetLocalPosition(worldPosition - parentPosition);
        }
        else
        {
            SetLocalPosition(worldPosition);
        }
    }

    void TransformComponent::SetWorldX(float x)
    {
        SetWorldPosition({x, GetWorldPosition().y});
    }

    void TransformComponent::SetWorldY(float y)
    {
        SetWorldPosition({ GetWorldPosition().x, y });
    }

    void TransformComponent::SetZIndex(float z)
    {
        m_ZIndex = z;
    }

    vec2 TransformComponent::GetWorldPosition() const
    {
        UpdateWorldPosition();
        return m_WorldPosition;
    }

    float TransformComponent::GetZIndex() const
    {
        return m_ZIndex;
    }

    void TransformComponent::SetParent(GameObject* newParentObj)
    {
        if (newParentObj == GetOwner() or std::ranges::find(m_ChildObjs, newParentObj) != m_ChildObjs.end() or m_ParentObj == newParentObj)
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
            m_ParentObj->GetTransform()->RemoveChild(GetOwner());

        m_ParentObj = newParentObj;

        if (m_ParentObj)
            m_ParentObj->GetTransform()->AddChild(GetOwner());
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
                m_WorldPosition = m_LocalPosition;
            }
            else
            {
                m_WorldPosition = m_ParentObj->GetTransform()->GetWorldPosition() + m_LocalPosition;
            }
            m_DirtyFlag = false;
        }
    }

    TransformComponent::TransformComponent(GameObject* owner)
        : BaseComponent{owner}
        , m_ChildObjs{}
        , m_LocalPosition{}
        , m_WorldPosition{}
        , m_ParentObj{nullptr}
        , m_DirtyFlag{true}
    {
        GetWorldPosition();
    }
}
