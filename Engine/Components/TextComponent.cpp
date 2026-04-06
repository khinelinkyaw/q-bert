#include "BaseComponent.h"
#include <Engine/Components/TextComponent.h>
#include <Engine/Rendering/Font.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Texture2D.h>
#include <Engine/ResourceManager.h>
#include <Engine/Utils/Colors.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdint>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <stdexcept>
#include <string>

using namespace GameEngine;

TextComponent::TextComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_needsUpdate(true)
    , m_text("")
    , m_color(Colors::WHITE)
    , m_font(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36))
    , m_textTexture(nullptr)
{
}

void TextComponent::FixedUpdate()
{
    if (m_needsUpdate)
    {
        const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_DestroySurface(surf);
        m_textTexture = std::make_shared<Texture2D>(texture);
        m_needsUpdate = false;
    }
}

void TextComponent::Update()
{
}

void TextComponent::Render(glm::vec3 const& pos) const
{
    if (m_textTexture != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
    }
}

void TextComponent::SetText(const std::string& text)
{
    m_text = text;
    m_needsUpdate = true;
}

void TextComponent::SetColor(const SDL_Color& color)
{
    m_color = color;
    m_needsUpdate = true;
}


