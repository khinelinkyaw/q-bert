#include "BaseComponent.h"
#include <cassert>

namespace GameEngine
{
    GameObject* BaseComponent::GetOwnerObject() const
    {
        return m_pOwner;
    }
    BaseComponent::BaseComponent(GameObject* owner)
        : m_pOwner{owner}
    {
        assert(m_pOwner != nullptr);
    }
}

