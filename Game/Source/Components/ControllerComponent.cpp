#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputMapping.h>

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/ControllerComponent.h>

#include <cassert>

using namespace Game;

void ControllerComponent::ProcessInput()
{
    // Where is the origin?
    // Top left is the origin (0,0)
    assert(m_pInputMapping != nullptr);

    if (m_pInputMapping->GetActionState("MoveUp", *m_pInputDevice))
    {
        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, Direction::UpLeft);
    }
    if (m_pInputMapping->GetActionState("MoveRight", *m_pInputDevice))
    {
        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, Direction::UpRight);
    }
    if (m_pInputMapping->GetActionState("MoveDown", *m_pInputDevice))
    {
        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, Direction::DownRight);
    }
    if (m_pInputMapping->GetActionState("MoveLeft", *m_pInputDevice))
    {
        GetOwner()->SendEvent<EventArgMove>("OnMove", MovementEvent::OnHop, Direction::DownLeft);
    }
}

void ControllerComponent::Update()
{
    ProcessInput();
}

void ControllerComponent::Init(GameEngine::InputMapping* pInputMapping, GameEngine::InputDevice* pInputDevice)
{
    m_pInputMapping = pInputMapping;
    m_pInputDevice = pInputDevice;
}

ControllerComponent::ControllerComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
}
