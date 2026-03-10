#include "ControllerComponent.h"
#include <Command.h>
#include <memory>

void dae::ControllerComponent::ClearCommands()
{
    m_Commands.clear();
}

void dae::ControllerComponent::ExecuteCommands()
{
    // ုဒီလိုလုပ်တာကောင်းမဲ့ပုံမပေါက်ဘူး။ လာမဲ့ အပတ် စာသင်ချိန်မှာ အပြောခံရဖို့ အခြေအနေရှိတယ်
    while (!m_Commands.empty())
    {
        m_Commands.front()->Execute(*m_pOwner);
        m_Commands.pop_front();
    }
}

void dae::ControllerComponent::FixedUpdate()
{
    ExecuteCommands();
}

void dae::ControllerComponent::Update()
{
}

void dae::ControllerComponent::Render(glm::vec3 const&) const
{
}

dae::ControllerComponent::ControllerComponent(float speed)
    : m_Speed{ speed }
    , m_Commands{}
{
}
