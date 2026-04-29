#ifndef UTILS_COLORS_H
#define UTILS_COLORS_H

#include <SDL3/SDL_pixels.h>

namespace GameEngine::Colors
{
    SDL_Color WHITE { 255, 255, 255, 255 };
    SDL_Color RED{ 255, 0, 0, 255 };
    SDL_Color GREEN{ 0, 255, 0, 255 };
    SDL_Color BLUE{ 0, 0, 255, 255 };
    SDL_Color BLACK{ 0, 0, 0, 255 };
}

#endif