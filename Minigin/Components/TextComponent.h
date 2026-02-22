#pragma once
#include "Components/BaseComponent.h"
#include <SDL3/SDL_pixels.h>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <string>

namespace dae
{
    class Font;
    class Texture2D;
    class TextComponent : public BaseComponent
    {
    public:
        void FixedUpdate() override;
        void Update(float deltaTime) override;
        void Render(glm::vec3 const& pos) const override;

        void SetText(const std::string& text);
        void SetColor(const SDL_Color& color);

        TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
        virtual ~TextComponent() = default;
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;
    private:
        bool m_needsUpdate{};
        std::string m_text{};
        SDL_Color m_color{ 255, 255, 255, 255 };
        std::shared_ptr<Font> m_font{};
        std::shared_ptr<Texture2D> m_textTexture{};

    };
}
