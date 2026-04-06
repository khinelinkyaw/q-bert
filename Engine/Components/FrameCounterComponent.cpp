#include "BaseComponent.h"
#include "FrameCounterComponent.h"
#include <Engine/Minigin.h>
#include <glm/fwd.hpp>
#include <string>

using namespace GameEngine;

FrameCounterComponent::FrameCounterComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_FramesPerSecond{}
    , m_AccumulatedTime{}
    , m_TextComponent{ owner, "FPS: 0" }
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
