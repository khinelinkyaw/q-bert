#include "BaseComponent.h"

namespace Engine
{
    void BaseComponent::SetOwner(GameObject* pOwner)
    {
        m_pOwner = pOwner;
    }
}

