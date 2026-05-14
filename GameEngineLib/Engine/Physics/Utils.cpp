#include <Engine/Physics/Utils.h>

using namespace GameEngine;

bool Collision::CollisionBetweenRects(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
    return (x1 < x2 + width2) &&
           (x1 + width1 > x2) &&
           (y1 < y2 + height2) &&
            (y1 + height1 > y2);
}

bool Collision::CollisionBetweenRectAndPoint(float rectX, float rectY, float rectWidth, float rectHeight, float pointX, float pointY)
{
    return (pointX >= rectX) &&
           (pointX <= rectX + rectWidth) &&
           (pointY >= rectY) &&
           (pointY <= rectY + rectHeight);
}
