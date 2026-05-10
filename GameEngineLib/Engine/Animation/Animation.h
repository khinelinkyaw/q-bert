#ifndef ANIMATION_H
#define ANIMATION_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Texture2D.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace GameEngine
{
    enum class AnimationType
    {
        OneOff,
        Loop
    };

    class SpriteComponent final : public BaseComponent
    {
    private:
        uint16_t m_SpriteIndex{};
        float m_SpriteDuration{};
        std::shared_ptr<Texture2D> m_Texture{};
        uint8_t m_Rows{};
        uint8_t m_Cols{};
        uint8_t m_TotalSprites{};
        std::vector<Rect<float>> m_SpriteRects{};

    public:
        Rect<float> GetSpriteRect(uint8_t index);
        void RenderSprite(uint8_t index);

        void FixedUpdate() override;
        void Update() override;
        void Render(vector3 const&) const override;

        void Init(std::string const& filePath, uint8_t rows, uint8_t cols, uint8_t totalSprites = 0);
        SpriteComponent(GameObject* owner);
        ~SpriteComponent() override = default;
    };
}

#endif