#ifndef ANIMATION_H
#define ANIMATION_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Misc/Types.h>
#include <Engine/Core/GameObject.h>

#include <string>
#include <vector>

namespace GameEngine
{
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
        void Render(vec2 const&) const override {};

        void Init(std::string const& filePath, int rows, int cols, int totalSprites = 0);
        SpriteComponent(GameObject* owner);
        ~SpriteComponent() override = default;
    };
}

#endif