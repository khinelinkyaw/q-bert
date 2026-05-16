#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>

#include <cassert>

namespace GameEngine
{
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

