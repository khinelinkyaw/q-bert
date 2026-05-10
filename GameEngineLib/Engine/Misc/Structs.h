#ifndef ENGINE_STRUCTS_H
#define ENGINE_STRUCTS_H
//
//#include <glm/fwd.hpp>
//
//#include <array>

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