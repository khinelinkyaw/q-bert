#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>

#include <SDL3/SDL_pixels.h>
#include <memory>
#include <string>

namespace GameEngine
{
    class Font;
    class Texture2D;
    class GameObject;

    class TextComponent final : public BaseComponent
    {
    private:
        bool m_needsUpdate;
        std::string m_text;
        SDL_Color m_color;
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;
        std::unique_ptr<Observer> m_Observer;

    public:
        void FixedUpdate() override;
        void Update() override;
        void Render(vector3 const& pos) const override;

        void SetText(const std::string& text);
        void SetColor(const SDL_Color& color);

        Observer* GetObserver();
        void SetObserver(std::unique_ptr<Observer>&& pObserver);

        //TextComponent(GameObject* owner, std::string const& text = "", std::string const& font_name = "Lingua.otf", uint8_t font_size = 36, SDL_Color const& color = { 255,255,0,255 });
        TextComponent(GameObject* owner);
        ~TextComponent() = default;
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;
    };
}

#endif