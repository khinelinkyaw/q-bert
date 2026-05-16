#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputMapping.h>

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/ControllerComponent.h>

#include <cassert>
#include <memory>
#include <utility>

using namespace Game;

void ControllerComponent::ProcessInput()
{
    // Where is the origin?
    // Top left is the origin (0,0)
    assert(m_pInputMapping != nullptr);

    if (m_pInputMapping->GetActionState("MoveUp", *m_pInputDevice))
    {
        std::unique_ptr<EventArgMove> eventArg{ std::make_unique<EventArgMove>(EventArgMove{"OnMove", MovementEvent::OnHop, FacingDir::UpLeft}) };
        GetOwner()->SendEvent(std::move(eventArg));
    }
    if (m_pInputMapping->GetActionState("MoveRight", *m_pInputDevice))
    {
        std::unique_ptr<EventArgMove> eventArg{ std::make_unique<EventArgMove>(EventArgMove{"OnMove", MovementEvent::OnHop, FacingDir::UpRight}) };
        GetOwner()->SendEvent(std::move(eventArg));
    }
    if (m_pInputMapping->GetActionState("MoveDown", *m_pInputDevice))
    {
        std::unique_ptr<EventArgMove> eventArg{ std::make_unique<EventArgMove>(EventArgMove{"OnMove", MovementEvent::OnHop, FacingDir::DownRight}) };
        GetOwner()->SendEvent(std::move(eventArg));
    }
    if (m_pInputMapping->GetActionState("MoveLeft", *m_pInputDevice))
    {
        std::unique_ptr<EventArgMove> eventArg{ std::make_unique<EventArgMove>(EventArgMove{"OnMove", MovementEvent::OnHop, FacingDir::DownLeft}) };
        GetOwner()->SendEvent(std::move(eventArg));
    }
}

void ControllerComponent::FixedUpdate()
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
