#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "../Modules/Texture2D.h"
#include "BaseComponent.h"
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

        TextureComponent();
        TextureComponent(const std::string& filename);
        ~TextureComponent() = default;
        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) noexcept = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
    };
}

#endif