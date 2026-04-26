#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Misc/GameObject.h>
#include <cassert>
#include <memory>

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

void ControllerComponent::ProcessInput()
{
    // Where is the origin?
    // Top left is the origin (0,0)
    assert(m_pInputDevice != nullptr);

    if (m_pInputDevice->IsDown(InputAction::MoveUp))
    {
        AddCommand<MoveCommand>(0.f, -1.0f);
    }
    if (m_pInputDevice->IsDown(InputAction::MoveRight))
    {
        AddCommand<MoveCommand>(1.f, 0.0f);
    }
    if (m_pInputDevice->IsDown(InputAction::MoveDown))
    {
        AddCommand<MoveCommand>(0.f, 1.0f);
    }
    if (m_pInputDevice->IsDown(InputAction::MoveLeft))
    {
        AddCommand<MoveCommand>(-1.f, 0.0f);
    }
    if (m_pInputDevice->IsReleased(InputAction::TakeDamage))
    {
        AddCommand<TakeDamageCommand>();
    }
    if (m_pInputDevice->IsReleased(InputAction::IncreaseScore))
    {
        AddCommand<IncreaseScore>();
    }
}

void ControllerComponent::FixedUpdate()
{
    ProcessInput();
    ExecuteCommands();
}

void ControllerComponent::Update()
{
}

void ControllerComponent::Render(glm::vec3 const&) const
{
}

ControllerComponent::ControllerComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Commands{}
    , m_Speed{ DEFAULT_SPEED }
{
}
