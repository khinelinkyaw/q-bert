#include <Engine/ResourceManager.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Components/TextureComponent.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <string>

using namespace GameEngine;

void TextureComponent::FixedUpdate()
{
}

void TextureComponent::Update()
{
}

void TextureComponent::Render(glm::vec3 const& pos) const
{
    if (m_texture != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }
}

void TextureComponent::SetTexture(const std::string& filename)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::TextureComponent()
    : m_texture{ nullptr }
{
}

TextureComponent::TextureComponent(const std::string& filename)
    : m_texture{ ResourceManager::GetInstance().LoadTexture(filename) }
{
}
