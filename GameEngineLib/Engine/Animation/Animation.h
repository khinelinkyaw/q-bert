#ifndef ANIMATION_H
#define ANIMATION_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Components/TextureComponent.h>

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
        TextureComponent* m_TextureComponent{};
        std::vector<Rect<float>> m_SpriteRects{};
        int m_TotalSprites{};

    public:
        void SetSpriteIndex(int index);

        void FixedUpdate() override {};
        void Update() override {};
        void Render(vector3 const&) const override {};

        void Init(std::string const& filePath, int rows, int cols, int totalSprites = 0);
        SpriteComponent(GameObject* owner);
        ~SpriteComponent() override = default;
    };
}

#endif