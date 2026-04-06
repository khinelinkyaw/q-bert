#ifndef UTILS_COLORS_H
#define UTILS_COLORS_H

#include <SDL3/SDL_pixels.h>

namespace GameEngine::Colors
{
    SDL_Color WHITE { 1, 1, 1, 1 };
    SDL_Color RED{ 1, 0, 0, 1 };
    SDL_Color GREEN{ 0, 1, 0, 1 };
    SDL_Color BLUE{ 0, 0, 1, 1 };
    SDL_Color BLACK{ 0, 0, 0, 1 };
}

#endif