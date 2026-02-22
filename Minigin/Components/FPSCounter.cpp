#include "FPSCounter.h"

dae::FrameCounterComponent::FrameCounterComponent()
    : m_FramesPerSecond{}
    , m_AccumulatedTime{}
    , m_TextComponent{ "FPS: 0" }
{
}

void dae::FrameCounterComponent::FixedUpdate()
{
    m_TextComponent.FixedUpdate();
}

void dae::FrameCounterComponent::Update(float deltaTime)
{
    m_AccumulatedTime += deltaTime;
    ++m_FramesPerSecond;

    if (m_AccumulatedTime >= 1.f)
    {
        m_TextComponent.SetText("FPS: " + std::to_string(static_cast<int>(m_FramesPerSecond)));
        m_FramesPerSecond = 0;
        m_AccumulatedTime -= 1.f;
    }
}

void dae::FrameCounterComponent::Render(glm::vec3 const& pos) const
{
    m_TextComponent.Render(pos);
}
