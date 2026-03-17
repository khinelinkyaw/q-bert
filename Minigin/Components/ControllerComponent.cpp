#include "ControllerComponent.h"
#include <Command.h>
#include <InputDevice.h>
#include <memory>

using namespace Engine;

void ControllerComponent::ClearCommands()
{
    m_Commands.clear();
}

void ControllerComponent::ExecuteCommands()
{
    // ုဒီလိုလုပ်တာကောင်းမဲ့ပုံမပေါက်ဘူး။ လာမဲ့ အပတ် စာသင်ချိန်မှာ အပြောခံရဖို့ အခြေအနေရှိတယ်
    while (!m_Commands.empty())
    {
        m_Commands.front()->Execute(*m_pOwner);
        m_Commands.pop_front();
    }
}

void ControllerComponent::ProcessInput(InputDevice& inputDevice)
{
    if (inputDevice.IsDown(InputAction::MoveUp))
    {
        AddCommand<MoveCommand>(0.f, -1.0f);
    }
    if (inputDevice.IsDown(InputAction::MoveRight))
    {
        AddCommand<MoveCommand>(1.f, 0.0f);
    }
    if (inputDevice.IsDown(InputAction::MoveDown))
    {
        AddCommand<MoveCommand>(0.f, 1.0f);
    }
    if (inputDevice.IsDown(InputAction::MoveLeft))
    {
        AddCommand<MoveCommand>(-1.f, 0.0f);
    }
}

void ControllerComponent::FixedUpdate()
{
    ExecuteCommands();
}

void ControllerComponent::Update()
{
}

void ControllerComponent::Render(glm::vec3 const&) const
{
}

ControllerComponent::ControllerComponent(float speed)
    : m_Commands{}
    , m_Speed{ speed }
{
}
