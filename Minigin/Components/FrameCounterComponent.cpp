#include "FrameCounterComponent.h"
#include "Minigin.h"
#include <glm/fwd.hpp>
#include <string>

using namespace Engine;

FrameCounterComponent::FrameCounterComponent()
    : m_FramesPerSecond{}
    , m_AccumulatedTime{}
    , m_TextComponent{ "FPS: 0" }
{
}

void FrameCounterComponent::FixedUpdate()
{
    m_TextComponent.FixedUpdate();
}

void FrameCounterComponent::Update()
{
    m_AccumulatedTime += Minigin::GetDeltaTime();
    ++m_FramesPerSecond;

    if (m_AccumulatedTime >= 1.f)
    {
        m_TextComponent.SetText("FPS: " + std::to_string(static_cast<int>(m_FramesPerSecond)));
        m_FramesPerSecond = 0;
        m_AccumulatedTime -= 1.f;
    }
}

void FrameCounterComponent::Render(glm::vec3 const& pos) const
{
    m_TextComponent.Render(pos);
}
