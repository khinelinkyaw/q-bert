#pragma once
#include <Engine/Components/BaseComponent.h>
#include <SDL3/SDL_pixels.h>
#include <cstdint>
#include <glm/fwd.hpp>
#include <memory>
#include <string>

namespace GameEngine
{
    class Font;
    class Texture2D;
    class TextComponent final : public BaseComponent
    {
    public:
        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const& pos) const override;

        void SetText(const std::string& text);
        void SetColor(const SDL_Color& color);

        TextComponent(GameObject* owner, std::string const& text = "", std::string const& font_name = "Lingua.otf", uint8_t font_size = 36, SDL_Color const& color = { 255,255,0,255 });
        ~TextComponent() = default;
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
