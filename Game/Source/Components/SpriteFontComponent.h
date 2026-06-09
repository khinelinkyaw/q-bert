#ifndef SPRITE_FONT_COMPONENT_H
#define SPRITE_FONT_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>

#include <vector>

namespace Game
{
    class SpriteFontComponent final : public GameEngine::BaseComponent
    {
    private:
        int m_MaxDigits{ 5 };
        std::vector<int> m_Digits{};
        GameEngine::SpriteComponent* m_pSpriteComponent{};
        GameEngine::TextureComponent* m_pTextureComponent{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& pos) const override;

        void UpdateNumber(int number);
        void UpdateMaxDigit(int maxDigits) { m_MaxDigits = maxDigits; }
        SpriteFontComponent(GameEngine::GameObject* owner);
        ~SpriteFontComponent() override = default;
    };
}

#endif