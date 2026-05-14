#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Texture2D.h>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include <glm/ext/vector_float2.hpp>

#include <cassert>
#include <stdexcept>
#include <string>

using namespace GameEngine;

Texture2D::~Texture2D()
{
    SDL_DestroyTexture(m_Texture);
}

glm::vec2 Texture2D::GetSize() const
{
    float w{}, h{};
    SDL_GetTextureSize(m_Texture, &w, &h);
    return { w, h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
    return m_Texture;
}

Texture2D::Texture2D(const std::string& fullPath)
{
    SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError()
        );
    }

    m_Texture = SDL_CreateTextureFromSurface(
        Renderer::Get().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!m_Texture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError()
        );
    }

    SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_PIXELART);
}

Texture2D::Texture2D(SDL_Texture* texture) : m_Texture{ texture }
{
    assert(m_Texture != nullptr);
}
