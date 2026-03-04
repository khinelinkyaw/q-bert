#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include <glm/fwd.hpp>

namespace dae
{
    class FrameCounterComponent final : public BaseComponent
    {
    public:
        void FixedUpdate() override;
        void Update(float deltaTime) override;
        void Render(glm::vec3 const& pos) const override;

        FrameCounterComponent();
        ~FrameCounterComponent() = default;
        FrameCounterComponent(const FrameCounterComponent& other) = delete;
        FrameCounterComponent(FrameCounterComponent&& other) = delete;
        FrameCounterComponent& operator=(const FrameCounterComponent& other) = delete;
        FrameCounterComponent& operator=(FrameCounterComponent&& other) = delete;
    private:
        float m_FramesPerSecond{};
        float m_AccumulatedTime{};
        TextComponent m_TextComponent{};
    };
}