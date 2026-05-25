#ifndef RENDERER_H
#define RENDERER_H

#include <Engine/Misc/Singleton.h>
#include <Engine/Misc/Types.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_rect.h>

#include <glm/glm.hpp>

namespace GameEngine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	private:
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
        void RenderTexture(const Texture2D& texture, SDL_FRect const& srcRect, SDL_FRect const& dstRect) const;

        void DrawLine(float x1, float y1, float x2, float y2, const SDL_Color& color) const;
        void DrawLine(glm::vec2 const& start, glm::vec2 const& end, const SDL_Color& color) const;
        void DrawLine(vec3 const& start, vec3 const& end, const SDL_Color& color) const;

        void DrawRect(float x, float y, float width, float height, const SDL_Color& color) const;
        void DrawRect(glm::vec2 const& pos, glm::vec2 const& size, const SDL_Color& color) const;
        void DrawRect(vec3 const& pos, glm::vec2 const& size, const SDL_Color& color) const;
        void DrawRect(SDL_FRect const& rect, const SDL_Color& color) const;

        void DrawPoint(float centerX, float centerY, const SDL_Color& color) const;
        void DrawPoint(glm::vec2 const& center, const SDL_Color& color) const;
        void DrawPoint(vec3 const& center, const SDL_Color& color) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		bool SetRenderLogicalPresentation(int width, int height);
	};
}

#endif