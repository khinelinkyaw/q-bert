#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>

#include <cassert>

namespace GameEngine
{
    void BaseComponent::OnCollisionEnter(GameObject*) const
    {
    }
    void BaseComponent::OnCollisionStay(GameObject*) const
    {
    }
    void BaseComponent::OnCollisionExit(GameObject*) const
    {
    }
    void BaseComponent::OnEvent(EventArg*)
    {
    }
    GameObject* BaseComponent::GetOwner() const
    {
        return m_pOwner;
    }

    BaseComponent::BaseComponent(GameObject* owner)
        : m_pOwner{owner}
    {
        assert(m_pOwner != nullptr);
    }
}

