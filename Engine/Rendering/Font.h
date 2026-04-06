#pragma once
#include <string>

struct TTF_Font;
namespace GameEngine
{
	/**
	 * Simple RAII wrapper for a TTF_Font
	 */
	class Font final
	{
	public:
		// TODO: Make it so that the font can be changed
		TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, float size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		// Change it to a unique ptr
		TTF_Font* m_font;
	};
}
