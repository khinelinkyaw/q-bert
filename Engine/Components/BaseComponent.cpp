#include "BaseComponent.h"
#include <cassert>

namespace GameEngine
{
    void BaseComponent::SetOwner(GameObject* pOwner)
    {
        m_pOwner = pOwner;
    }

    BaseComponent::BaseComponent(GameObject* owner)
        : m_pOwner{owner}
    {
        assert(m_pOwner != nullptr);
    }
}

