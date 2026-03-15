#include "../ResourceManager.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <string>

void Engine::TextureComponent::FixedUpdate()
{
}

void Engine::TextureComponent::Update()
{
}

void Engine::TextureComponent::Render(glm::vec3 const& pos) const
{
    if (m_texture != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }
}

void Engine::TextureComponent::SetTexture(const std::string& filename)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

Engine::TextureComponent::TextureComponent()
    : m_texture{ nullptr }
{
}

Engine::TextureComponent::TextureComponent(const std::string& filename)
    : m_texture{ ResourceManager::GetInstance().LoadTexture(filename) }
{
}
