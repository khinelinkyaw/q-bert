#include <Engine/Core/SceneManager.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Texture2D.h>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <SDL3/SDL_pixels.h>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace GameEngine;

void Renderer::Init(SDL_Window* window)
{
    m_window = window;

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

#if defined(__EMSCRIPTEN__)
    m_renderer = SDL_CreateRenderer(window, nullptr);
#else
    m_renderer = SDL_CreateRenderer(window, nullptr);
#endif

    if (m_renderer == nullptr)
    {
        std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
        throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
    }
}

void Renderer::Render() const
{
    const auto& color = GetBackgroundColor();
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);

    SceneManager::Get().Render();

    SDL_RenderPresent(m_renderer);
}

void Renderer::Destroy()
{
    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
    SDL_FRect dst{};
    dst.x = x;
    dst.y = y;
    SDL_GetTextureSize(texture.GetSDLTexture(), &dst.w, &dst.h);
    SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
    SDL_FRect dst{};
    dst.x = x;
    dst.y = y;
    dst.w = width;
    dst.h = height;
    SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void GameEngine::Renderer::RenderTexture(const Texture2D& texture, SDL_FRect const& srcRect, SDL_FRect const& dstRect) const
{
    SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}

void GameEngine::Renderer::DrawLine(float x1, float y1, float x2, float y2, const SDL_Color& color) const
{
    SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(GetSDLRenderer(), x1, y1, x2, y2);
}

void GameEngine::Renderer::DrawLine(glm::vec2 const& start, glm::vec2 const& end, const SDL_Color& color) const
{
    DrawLine(start.x, start.y, end.x, end.y, color);
}

void GameEngine::Renderer::DrawLine(vec3 const& start, vec3 const& end, const SDL_Color& color) const
{
    DrawLine(start.x, start.y, end.x, end.y, color);
}

void GameEngine::Renderer::DrawRect(float x, float y, float width, float height, const SDL_Color& color) const
{
    SDL_FRect rect{ x, y, width, height };
    DrawRect(rect, color);
}

void GameEngine::Renderer::DrawRect(glm::vec2 const& pos, glm::vec2 const& size, const SDL_Color& color) const
{
    DrawRect(pos.x, pos.y, size.x, size.y, color);
}

void GameEngine::Renderer::DrawRect(vec3 const& pos, glm::vec2 const& size, const SDL_Color& color) const
{
    DrawRect(pos.x, pos.y, size.x, size.y, color);
}

void GameEngine::Renderer::DrawRect(SDL_FRect const& rect, const SDL_Color& color) const
{
    SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderRect(GetSDLRenderer(), &rect);
}

void GameEngine::Renderer::DrawPoint(float centerX, float centerY, const SDL_Color& color) const
{
    SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderPoint(GetSDLRenderer(), centerX, centerY);
}

void GameEngine::Renderer::DrawPoint(glm::vec2 const& center, const SDL_Color& color) const
{
    DrawPoint(center.x, center.y, color);
}

void GameEngine::Renderer::DrawPoint(vec3 const& center, const SDL_Color& color) const
{
    DrawPoint(center.x, center.y, color);
}

SDL_Renderer* Renderer::GetSDLRenderer() const { return m_renderer; }

bool GameEngine::Renderer::SetRenderLogicalPresentation(int width, int height)
{
    return SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}
