#include <Engine/Audio/SoundSystem.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Decoupling/Command.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/ServiceLocator.h>
#include <Engine/Misc/Enums.h>

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
    assert(m_pInputMapping != nullptr);

    if (m_pInputMapping->GetActionState("MoveUp"))
    {
        AddCommand<MoveCommand>(0.f, -1.0f);

        ServiceLocator::GetInstance().GetSoundSystem().Play(0);
    }
    if (m_pInputMapping->GetActionState("MoveRight"))
    {
        AddCommand<MoveCommand>(1.f, 0.0f);
    }
    if (m_pInputMapping->GetActionState("MoveDown"))
    {
        AddCommand<MoveCommand>(0.f, 1.0f);
    }
    if (m_pInputMapping->GetActionState("MoveLeft"))
    {
        AddCommand<MoveCommand>(-1.f, 0.0f);
    }
}

void ControllerComponent::FixedUpdate()
{
    ProcessInput();
    ExecuteCommands();
}

ControllerComponent::ControllerComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_pInputMapping{ std::make_unique<InputMapping>() }
{
    m_pInputMapping->SetInputDevice(&GameEngine::InputManager::GetInstance().GetGamepadInputDevice(0));
    m_pInputMapping->SetActionMapping("MoveUp", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_UP, GameEngine::InputCode::GP_BUTTON_DPAD_UP);
    m_pInputMapping->SetActionMapping("MoveDown", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_DOWN, GameEngine::InputCode::GP_BUTTON_DPAD_DOWN);
    m_pInputMapping->SetActionMapping("MoveLeft", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_LEFT, GameEngine::InputCode::GP_BUTTON_DPAD_LEFT);
    m_pInputMapping->SetActionMapping("MoveRight", GameEngine::InputActionType::Pressed, GameEngine::InputCode::KB_RIGHT, GameEngine::InputCode::GP_BUTTON_DPAD_RIGHT);
}
