#include "BaseComponent.h"

namespace GameEngine
{
    void BaseComponent::SetOwner(GameObject* pOwner)
    {
        m_pOwner = pOwner;
    }
}

