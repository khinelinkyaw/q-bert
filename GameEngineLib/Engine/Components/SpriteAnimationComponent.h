#ifndef SPRITE_ANIMATION_COMPONENT_H
#define SPRITE_ANIMATION_COMPONENT_H

#include <Engine/Components/BaseComponent.h>

#include <vector>

namespace GameEngine
{
    enum class AnimationType
    {
        Once,
        Loop
    };

    class SpriteComponent;
    class TextureComponent;
    class SpriteAnimationComponent final : public BaseComponent
    {
    private:
        std::vector<int> m_FrameIndices{};
        SpriteComponent* m_pSpriteComponent{};
        AnimationType m_AnimationType{ AnimationType::Loop };
        float m_FrameDuration{};
        float m_ElapsedTime{};
        int m_CurrentFrame{};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};

        void Init(AnimationType animationType, float frameDuration, std::vector<int> const& frameIndices);
        SpriteAnimationComponent(GameObject* owner);
        ~SpriteAnimationComponent() override = default;
    };
}

#endif
