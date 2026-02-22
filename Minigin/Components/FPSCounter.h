#pragma once
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include <SDL3/SDL_pixels.h>
#include <glm/fwd.hpp>
#include <memory>
#include <string>

namespace dae
{
    class FrameCounterComponent final : public BaseComponent
    {
    public:
        void FixedUpdate() = 0;
        void Update(float deltaTime) override;
        void Render(glm::vec3 const& pos) const override;

        FrameCounterComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
        virtual ~FrameCounterComponent() = default;
        FrameCounterComponent(const FrameCounterComponent& other) = delete;
        FrameCounterComponent(FrameCounterComponent&& other) = delete;
        FrameCounterComponent& operator=(const FrameCounterComponent& other) = delete;
        FrameCounterComponent& operator=(FrameCounterComponent&& other) = delete;
    private:
        float m_FramesPerSecond{};
        float m_AccumulatedTime{};
        TextComponent m_TextComponent;
    };
}