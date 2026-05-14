#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <Engine/Misc/Structs.h>

namespace GameEngine
{
    class Collision final
    {
    public:
        static bool CollisionBetweenRects(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

        template<typename T>
        static bool CollisionBetweenRects(Rect<T> const& rect1, Rect<T> const& rect2)
        {
            return CollisionBetweenRects(rect1.x, rect1.y, rect1.width, rect1.height, rect2.x, rect2.y, rect2.width, rect2.height);
        }

        static bool CollisionBetweenRectAndPoint(float rectX, float rectY, float rectWidth, float rectHeight, float pointX, float pointY);

        template<typename T>
        static bool CollisionBetweenRectAndPoint(Rect<T> const& rect, float pointX, float pointY)
        {
            return CollisionBetweenRectAndPoint(rect.x, rect.y, rect.width, rect.height, pointX, pointY);
        }
    };
}

#endif