#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "../Game/Main.cpp"
#include <filesystem>

namespace fs = std::filesystem;

int main(int, char* [])
{
#if __EMSCRIPTEN__
    fs::path data_location = "";
#else
    fs::path data_location = "./Data/";
    if (!fs::exists(data_location))
        data_location = "../Data/";
#endif
    Engine::Minigin engine(data_location);
    engine.Run(Game::load);
    return 0;
}
