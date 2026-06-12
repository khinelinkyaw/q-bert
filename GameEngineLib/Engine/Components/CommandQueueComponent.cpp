#include "CommandQueueComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>

using namespace GameEngine;

void CommandQueueComponent::ClearCommands()
{
    while (!m_CommandQueue.empty())
    {
        m_CommandQueue.pop();
    }
}

void CommandQueueComponent::HandleCommands()
{
    while (!m_CommandQueue.empty())
    {
        m_CommandQueue.front()->Execute(*GetOwner());
        m_CommandQueue.pop();
    }
}

GameEngine::CommandQueueComponent::CommandQueueComponent(GameObject* owner)
    : BaseComponent{ owner }
{
}
