#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/UI/Utils.h>
#include <Engine/Events/EventArgTexture.h>
#include <Engine/Misc/Types.h>

#include <glm/fwd.hpp>

#include <SDL3/SDL_rect.h>

#include <cmath>
#include <string>

using namespace GameEngine;

void GameEngine::TextureComponent::CalculateOrigin()
{
    Rect<float> rect{ 0.f, 0.f, m_SrcRect.width, m_SrcRect.height };

    m_Origin = GameEngine::UI::AlignToRect(m_Offset.x, m_Offset.y, rect, m_Pivot);
}

void TextureComponent::Render(vec2 const& pos) const
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

        Renderer::Get().RenderTexture(*m_Texture, &srcRect, &dstRect, m_Rotation);
    }
}

void TextureComponent::SetTexture(std::string const& filename)
{
    m_Texture = ResourceManager::Get().LoadTexture(filename);

    if (m_Texture != nullptr)
    {
        auto textureSize{ m_Texture->GetSize() };
        m_SrcRect = Rect<float>{ 0.f, 0.f, textureSize.x, textureSize.y };
        CalculateOrigin();

        GetOwner()->SendEvent<EventArgTexture>("TextureChanged", this);
    }
}

void GameEngine::TextureComponent::SetOriginOffset(glm::vec2 offset)
{
    m_Offset = offset;
    CalculateOrigin();
}

void GameEngine::TextureComponent::SetPivot(Pivot pivot)
{
    m_Pivot = pivot;
    CalculateOrigin();
}
//
//void GameEngine::TextureComponent::SetSrcRect(float x, float y, float width, float height)
//{
//    m_SrcRect = Rect<float>{ x, y, width, height };
//}

void GameEngine::TextureComponent::SetSrcRect(Rect<float> const& newSrcRect)
{
    if (m_SrcRect != newSrcRect)
    {
        m_SrcRect = newSrcRect;
        GetOwner()->SendEvent<EventArgTexture>("SourceRectChanged", this);
        CalculateOrigin();
    }
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

void GameEngine::TextureComponent::SetRotation(double rotation)
{
    m_Rotation = std::fmod(rotation, 360.0);
}

TextureComponent::TextureComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Texture{ nullptr }
{
}
