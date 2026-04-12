#pragma once
#include <Engine/Components/BaseComponent.h>
#include <SDL3/SDL_pixels.h>
#include <glm/fwd.hpp>
#include <memory>
#include <string>
#include <vector>

namespace GameEngine
{
    class Font;
    class Texture2D;
    class GameObject;
    //class Observer;
    class TextComponent final : public BaseComponent
    {
    public:
        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const& pos) const override;

        void SetText(std::string const& text);
        void SetColor(SDL_Color const& color);

        void OnNotify(GameObject const& gameObject, std::string eventId);
        //void AddObserver(std::unique_ptr<Observer> newObserver);

        //TextComponent(GameObject* owner, std::string const& text = "", std::string const& font_name = "Lingua.otf", uint8_t font_size = 36, SDL_Color const& color = { 255,255,0,255 });
        TextComponent(GameObject* owner);
        ~TextComponent() = default;
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;
    private:
        std::string m_text{};
        // TODO: Construct the font outside
        std::shared_ptr<Font> m_font{};
        std::shared_ptr<Texture2D> m_textTexture{};
        //std::vector<std::unique_ptr<Observer>>* m_pObservers{};
        SDL_Color m_color{ 255, 255, 255, 255 };
        bool m_needsUpdate{};
    };
}
