#pragma once
#include "ResourceManager.h"
#include "TextComponent.h"
#include <SDL3/SDL_pixels.h>
#include <memory>
#include <string>

namespace dae
{
    class FPSCounter final : public TextComponent
    {
    public:
        void Update(float deltaTime) override;

        FPSCounter(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
        virtual ~FPSCounter() = default;
        FPSCounter(const FPSCounter& other) = delete;
        FPSCounter(FPSCounter&& other) = delete;
        FPSCounter& operator=(const FPSCounter& other) = delete;
        FPSCounter& operator=(FPSCounter&& other) = delete;
    private:
        float m_FramesPerSecond{};
        float m_AccumulatedTime{};
    };
}