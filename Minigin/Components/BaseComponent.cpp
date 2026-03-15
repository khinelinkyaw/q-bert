#include "BaseComponent.h"

void Engine::BaseComponent::SetOwner(GameObject* pOwner)
{
    m_pOwner = pOwner;
}
