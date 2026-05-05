#include "Structs.h"

bool GameEngine::Rect::IsColliding(Rect const& other)
{
    return (
        this->x < other.x + other.width &&
        this->x + this->width > other.x &&
        this->y < other.y + other.height &&
        this->y + this->height > other.y
        );
}
