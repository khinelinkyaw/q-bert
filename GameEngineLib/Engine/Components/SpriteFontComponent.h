#ifndef SPRITE_FONT_COMPONENT_H
#define SPRITE_FONT_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
    enum class SpecialChars
    {
        Space = -1,
        NewLine = -2
    };

    class SpriteFontComponent final : public BaseComponent
    {
    private:
        std::unordered_map<char, int> m_CharToIndexMap{
            {' ', static_cast<int>(SpecialChars::Space)},
            {'\n', static_cast<int>(SpecialChars::NewLine)}
        };

        std::vector<int> m_Text{};
        SpriteComponent* m_pSpriteComponent{};
        TextureComponent* m_pTextureComponent{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& pos) const override;

        int GetTextLength() const { return static_cast<int>(m_Text.size()); }

        void SetText(std::string const& text);
        SpriteFontComponent(GameObject* owner);
        ~SpriteFontComponent() override = default;
    };
}

#endif