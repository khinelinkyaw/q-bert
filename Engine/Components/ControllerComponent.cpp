#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/GameObject.h>
#include <cassert>
#include <memory>
#include <utility>

using namespace GameEngine;

void ControllerComponent::ClearCommands()
{
    m_Commands.clear();
}

void ControllerComponent::ExecuteCommands()
{
    while (!m_Commands.empty())
    {
        m_Commands.front()->Execute(*GetOwnerObject());
        m_Commands.pop_front();
    }
}

void GameEngine::ControllerComponent::SetInputMappings(InputMapping const& inputMappings)
{
    m_InputMappings = std::make_unique<InputMapping>(inputMappings);
    m_InputMappings->SetInputDeviceType(m_pInputDevice->GetType());
}

void ControllerComponent::ProcessInput()
{
    // Where is the origin?
    // Top left is the origin (0,0)
    assert(m_pInputDevice != nullptr);

    if (m_pInputDevice->IsDown(m_InputMappings->GetInputKey("MoveUp")))
    {
        AddCommand<MoveCommand>(0.f, -1.0f);
    }
    if (m_pInputDevice->IsDown(m_InputMappings->GetInputKey("MoveRight")))
    {
        AddCommand<MoveCommand>(1.f, 0.0f);
    }
    if (m_pInputDevice->IsDown(m_InputMappings->GetInputKey("MoveDown")))
    {
        AddCommand<MoveCommand>(0.f, 1.0f);
    }
    if (m_pInputDevice->IsDown(m_InputMappings->GetInputKey("MoveLeft")))
    {
        AddCommand<MoveCommand>(-1.f, 0.0f);
    }
    if (m_pInputDevice->IsReleased(m_InputMappings->GetInputKey("TakeDamage")))
    {
        AddCommand<TakeDamageCommand>();
    }
    if (m_pInputDevice->IsReleased(m_InputMappings->GetInputKey("IncreaseScore")))
    {
        AddCommand<IncreaseScore>();
    }
}

void ControllerComponent::FixedUpdate()
{
    ProcessInput();
    ExecuteCommands();
}

ControllerComponent::ControllerComponent(GameObject* owner)
    : BaseComponent{owner}
{
}
