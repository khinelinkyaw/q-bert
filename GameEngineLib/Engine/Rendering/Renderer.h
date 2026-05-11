#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <Engine/Misc/Singleton.h>

#include <glm/glm.hpp>

namespace GameEngine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

        void DrawLine(float x1, float y1, float x2, float y2, const SDL_Color& color) const;
        void DrawLine(glm::vec2 const& start, glm::vec2 const& end, const SDL_Color& color) const;
        void DrawLine(glm::vec3 const& start, glm::vec3 const& end, const SDL_Color& color) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		bool SetRenderLogicalPresentation(int width, int height);
	};
}

#endif