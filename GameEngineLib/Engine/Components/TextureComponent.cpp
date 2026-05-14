#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/UI/Utils.h>
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
        Renderer::Get().RenderTexture(*m_texture, pos.x - m_Origin.x, pos.y - m_Origin.y);
    }
}

void TextureComponent::SetTexture(std::string const& filename)
{
    m_texture = ResourceManager::Get().LoadTexture(filename);
}

void GameEngine::TextureComponent::SetOrigin(float x, float y, Pivot pivot)
{
    auto textureSize{ m_texture->GetSize() };
    Rect<float> srcRect{0.f, 0.f, textureSize.x, textureSize.y};

    m_Origin = GameEngine::UI::AlignToRect(x, y, srcRect, pivot);
}

void GameEngine::TextureComponent::SetOrigin(glm::vec2 origin, Pivot pivot)
{
    SetOrigin(origin.x, origin.y, pivot);
}

TextureComponent::TextureComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_texture{ nullptr }
{
}
