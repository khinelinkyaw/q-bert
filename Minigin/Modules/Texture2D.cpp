#include "Renderer.h"
#include "Texture2D.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <cassert>
#include <glm/ext/vector_float2.hpp>
#include <stdexcept>
#include <string>

Engine::Texture2D::~Texture2D()
{
    SDL_DestroyTexture(m_texture);
}

glm::vec2 Engine::Texture2D::GetSize() const
{
    float w{}, h{};
    SDL_GetTextureSize(m_texture, &w, &h);
    return { w, h };
}

SDL_Texture* Engine::Texture2D::GetSDLTexture() const
{
    return m_texture;
}

Engine::Texture2D::Texture2D(const std::string& fullPath)
{
    SDL_Surface* surface = SDL_LoadPNG(fullPath.c_str());
    if (!surface)
    {
        throw std::runtime_error(
            std::string("Failed to load PNG: ") + SDL_GetError()
        );
    }

    m_texture = SDL_CreateTextureFromSurface(
        Renderer::GetInstance().GetSDLRenderer(),
        surface
    );

    SDL_DestroySurface(surface);

    if (!m_texture)
    {
        throw std::runtime_error(
            std::string("Failed to create texture from surface: ") + SDL_GetError()
        );
    }
}

Engine::Texture2D::Texture2D(SDL_Texture* texture) : m_texture{ texture }
{
    assert(m_texture != nullptr);
}

