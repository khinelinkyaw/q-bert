#ifndef PHYSICS_STRUCTS_H
#define PHYSICS_STRUCTS_H

namespace GameEngine
{
    struct Rect
    {
        float x;
        float y;
        float width;
        float height;

        bool IsColliding(Rect const& other);
    };
}

#endif