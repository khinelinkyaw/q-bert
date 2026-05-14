#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/UI/Utils.h>
#include <Engine/Core/GameObject.h>

#include <glm/fwd.hpp>

#include <SDL3/SDL_rect.h>

#include <string>

using namespace GameEngine;

void TextureComponent::Render(glm::vec3 const& pos) const
{
    if (m_Texture != nullptr)
    {
        SDL_FRect srcRect = m_SrcRect.ToSDLRect();
        SDL_FRect dstRect{
            pos.x - m_Origin.x,
            pos.y - m_Origin.y,
            m_SrcRect.width,
            m_SrcRect.height
        };

        Renderer::Get().RenderTexture(*m_Texture, srcRect, dstRect);
    }
}

void TextureComponent::SetTexture(std::string const& filename)
{
    m_Texture = ResourceManager::Get().LoadTexture(filename);

    if (m_Texture != nullptr)
    {
        auto textureSize{ m_Texture->GetSize() };
        m_SrcRect = Rect<float>{ 0.f, 0.f, textureSize.x, textureSize.y };
    }
}

void TextureComponent::SetOrigin(float x, float y, Pivot pivot)
{
    Rect<float> rect{0.f, 0.f, m_SrcRect.width, m_SrcRect.height};

    m_Origin = GameEngine::UI::AlignToRect(x, y, rect, pivot);
}

void TextureComponent::SetOrigin(glm::vec2 origin, Pivot pivot)
{
    SetOrigin(origin.x, origin.y, pivot);
}

void GameEngine::TextureComponent::SetSrcRect(float x, float y, float width, float height)
{
    m_SrcRect = Rect<float>{ x, y, width, height };
}

void GameEngine::TextureComponent::SetSrcRect(Rect<float> const& srcRect)
{
    m_SrcRect = srcRect;
}

Rect<float> TextureComponent::GetSrcRect() const
{
    return m_SrcRect;
}

Rect<float> GameEngine::TextureComponent::GetTextureSize() const
{
    auto textureSize{ m_Texture->GetSize() };

    return Rect<float>{
        0.f,
        0.f,
        textureSize.x,
        textureSize.y
    };
}

TextureComponent::TextureComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Texture{ nullptr }
{
}
