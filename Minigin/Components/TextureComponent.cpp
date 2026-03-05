#include "../ResourceManager.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <string>

void dae::TextureComponent::FixedUpdate()
{
}

void dae::TextureComponent::Update(float)
{
}

void dae::TextureComponent::Render(glm::vec3 const& pos) const
{
    if (m_texture != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

dae::TextureComponent::TextureComponent()
    : m_texture{ nullptr }
{
}

dae::TextureComponent::TextureComponent(const std::string& filename)
    : m_texture{ ResourceManager::GetInstance().LoadTexture(filename) }
{
}
