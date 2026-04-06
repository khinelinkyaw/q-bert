#include "BaseComponent.h"
#include <cassert>

namespace GameEngine
{
    BaseComponent::BaseComponent(GameObject* owner)
        : m_pOwner{owner}
    {
        assert(m_pOwner != nullptr);
    }
}

