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
    if (m_Texture != nullptr)
    {
        Renderer::Get().RenderTexture(*m_Texture, pos.x - m_Origin.x, pos.y - m_Origin.y);
    }
}

void TextureComponent::SetTexture(std::string const& filename)
{
    m_Texture = ResourceManager::Get().LoadTexture(filename);
}

void TextureComponent::SetOrigin(float x, float y, Pivot pivot)
{
    auto textureSize{ m_Texture->GetSize() };
    Rect<float> srcRect{0.f, 0.f, textureSize.x, textureSize.y};

    m_Origin = GameEngine::UI::AlignToRect(x, y, srcRect, pivot);
}

void TextureComponent::SetOrigin(glm::vec2 origin, Pivot pivot)
{
    SetOrigin(origin.x, origin.y, pivot);
}

glm::vec2 TextureComponent::GetOrigin() const
{
    auto worldPos{ GetOwnerObject()->GetTransform()->GetWorldPosition() };

    return glm::vec2{
            m_Origin.x + worldPos.x,
            m_Origin.y + worldPos.y
        };
}

Rect<float> TextureComponent::GetSize() const
{
    if (m_Texture != nullptr)
    {
        auto textureSize{ m_Texture->GetSize() };
        return Rect<float>{ 0.f, 0.f, textureSize.x, textureSize.y };
    }
    return Rect<float>{};
}

TextureComponent::TextureComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Texture{ nullptr }
{
}
