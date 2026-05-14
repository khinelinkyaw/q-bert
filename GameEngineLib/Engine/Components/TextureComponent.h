#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Rendering/Texture2D.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Structs.h>

#include <memory>
#include <string>

namespace GameEngine
{
    class TextureComponent final : public BaseComponent
    {
    private:
        glm::vec2 m_Origin{ 0.f, 0.f };
        Rect<float> m_SrcRect{};
        std::shared_ptr<Texture2D> m_Texture{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(glm::vec3 const& pos) const override;

        void SetTexture(const std::string& filename);
        void SetOrigin(float x, float y, Pivot pivot = Pivot::LeftUp);
        void SetOrigin(glm::vec2 origin, Pivot pivot = Pivot::LeftUp);

        void SetSrcRect(float x, float y, float width, float height);
        void SetSrcRect(Rect<float> const& srcRect);
        Rect<float> GetSrcRect() const;

        Rect<float> GetTextureSize() const;

        TextureComponent(GameObject* owner);
        ~TextureComponent() = default;
        TextureComponent(TextureComponent const& other) = delete;
        TextureComponent(TextureComponent&& other) noexcept = delete;
        TextureComponent& operator=(TextureComponent const& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
    };
}

#endif