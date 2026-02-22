#include "FPSCounter.h"

void dae::FrameCounterComponent::Update(float deltaTime)
{
    m_AccumulatedTime += deltaTime;
    ++m_FramesPerSecond;

    if (m_AccumulatedTime >= 1.f)
    {
        SetText("FPS: " + std::to_string(static_cast<int>(m_FramesPerSecond)));
        m_FramesPerSecond = 0;
        m_AccumulatedTime -= 1.f;
    }
}

void dae::FrameCounterComponent::Render(glm::vec3 const& pos) const
{
}

dae::FrameCounterComponent::FrameCounterComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
    : TextComponent(text, std::move(font), color)
    , m_FramesPerSecond(0)
    , m_AccumulatedTime(0.f)
{
}

