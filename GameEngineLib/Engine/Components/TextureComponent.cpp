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
    Rect<float> rect{ 0.f, 0.f, m_SourceRect.width, m_SourceRect.height };

    m_Origin = GameEngine::UI::AlignToRect(m_Offset.x, m_Offset.y, rect, m_Pivot);
}

void TextureComponent::Render(vec2 const& pos) const
{
    if (m_Texture != nullptr and Visible == true)
    {
        SDL_FRect srcRect = m_SourceRect.ToSDLRect();
        SDL_FRect dstRect{
            pos.x - m_Origin.x,
            pos.y - m_Origin.y,
            m_SourceRect.width,
            m_SourceRect.height
        };

        Renderer::Get().RenderTexture(*m_Texture, &srcRect, &dstRect, m_Rotation);
    }

    //SDL_FRect srcRect = m_SourceRect.ToSDLRect();
    //SDL_FRect dstRect{
    //    pos.x - m_Origin.x,
    //    pos.y - m_Origin.y,
    //    m_SourceRect.width,
    //    m_SourceRect.height
    //};

    //Renderer::Get().DrawRect(dstRect, SDL_Color{ 255, 0, 0, 255 });
}

void TextureComponent::SetTexture(std::string const& filename)
{
    m_Texture = ResourceManager::Get().LoadTexture(filename);

    if (m_Texture != nullptr)
    {
        auto textureSize{ m_Texture->GetSize() };
        m_SourceRect = Rect<float>{ 0.f, 0.f, textureSize.x, textureSize.y };
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

void GameEngine::TextureComponent::SetSourceRect(Rect<float> const& newSrcRect)
{
    if (m_SourceRect != newSrcRect)
    {
        m_SourceRect = newSrcRect;
        GetOwner()->SendEvent<EventArgTexture>("SourceRectChanged", this);
        CalculateOrigin();
    }
}

Rect<float> TextureComponent::GetSourceRect() const
{
    return m_SourceRect;
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
