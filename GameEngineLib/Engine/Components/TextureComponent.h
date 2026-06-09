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
        double m_Rotation{ 0.0 };
        glm::vec2 m_Origin{ 0.f, 0.f };
        glm::vec2 m_Offset{ 0.f, 0.f };
        Pivot m_Pivot{ Pivot::LeftUp };
        Rect<float> m_SrcRect{};
        std::shared_ptr<Texture2D> m_Texture{};

        void CalculateOrigin();

    public:
        bool Visible{ true };

        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const& pos) const override;

        void SetTexture(const std::string& filename);
        
        glm::vec2 GetOrigin() const { return m_Origin; }
        void SetOriginOffset(glm::vec2 offset);
        void SetPivot(Pivot pivot);

        //void SetSrcRect(float x, float y, float width, float height);
        void SetSrcRect(Rect<float> const& srcRect);
        Rect<float> GetSrcRect() const;

        Rect<float> GetTextureSize() const;

        void SetRotation(double rotation);

        TextureComponent(GameObject* owner);
        ~TextureComponent() = default;
        TextureComponent(TextureComponent const& other) = delete;
        TextureComponent(TextureComponent&& other) noexcept = delete;
        TextureComponent& operator=(TextureComponent const& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
    };
}

#endif