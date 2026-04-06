#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/Rendering/Texture2D.h>
#include <glm/fwd.hpp>
#include <memory>
#include <string>

namespace GameEngine
{
    class TextureComponent final : public BaseComponent
    {
    private:
        std::shared_ptr<Texture2D> m_texture{};
    public:
        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const& pos) const override;

        void SetTexture(const std::string& filename);

        TextureComponent(GameObject* owner);
        //TextureComponent(GameObject* owner, std::string const& filename);
        ~TextureComponent() = default;
        TextureComponent(TextureComponent const& other) = delete;
        TextureComponent(TextureComponent&& other) noexcept = delete;
        TextureComponent& operator=(TextureComponent const& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
    };
}

#endif