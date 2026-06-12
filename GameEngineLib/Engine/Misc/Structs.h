#ifndef ENGINE_STRUCTS_H
#define ENGINE_STRUCTS_H

#include <SDL3/SDL_rect.h>
//#include <array>

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

namespace GameEngine
{
    template<typename T>
    struct Rect
    {
        T x{};
        T y{};
        T width{};
        T height{};

        Rect() = default;
        Rect(T _x, T _y, T _width, T _height);

        Rect<T>& operator+(glm::vec2 const& offset)
        {
            x += offset.x;
            y += offset.y;
            return *this;
        }

        Rect<T>& operator-(glm::vec2 const& offset)
        {
            x -= offset.x;
            y -= offset.y;
            return *this;
        }

        bool operator==(Rect<T> const& other)
        {
            return (x == other.x and y == other.y and width == other.width and height == other.height);
        }

        SDL_FRect ToSDLRect() const
        {
            return SDL_FRect{ x, y, width, height };
        }
    };

    template<typename T>
    inline Rect<T>::Rect(T _x, T _y, T _width, T _height)
        : x{_x}
        , y{_y}
        , width{_width}
        , height{_height}
    {
    }
}

#endif