#include <Engine/Audio/SoundSystem.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Input/InputDevice.h>

#include <Components/ControllerComponent.h>
#include <Commands/PlayerCommands.h>

#include <cassert>
#include <memory>

using namespace Game;

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
    assert(m_pInputMapping != nullptr);

    if (m_pInputMapping->GetActionState("MoveUp", *m_pInputDevice))
    {
        AddCommand<MoveCommand>(0.f, -1.0f);

        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(0);
    }
    if (m_pInputMapping->GetActionState("MoveRight", *m_pInputDevice))
    {
        AddCommand<MoveCommand>(1.f, 0.0f);
    }
    if (m_pInputMapping->GetActionState("MoveDown", *m_pInputDevice))
    {
        AddCommand<MoveCommand>(0.f, 1.0f);
    }
    if (m_pInputMapping->GetActionState("MoveLeft", *m_pInputDevice))
    {
        AddCommand<MoveCommand>(-1.f, 0.0f);
    }
}

void ControllerComponent::FixedUpdate()
{
    ProcessInput();
    ExecuteCommands();
}

void ControllerComponent::Init(GameEngine::InputMapping* pInputMapping, GameEngine::InputDevice* pInputDevice, float speed)
{
    m_pInputMapping = pInputMapping;
    m_pInputDevice = pInputDevice;
    m_Speed = speed;
}

ControllerComponent::ControllerComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
}
