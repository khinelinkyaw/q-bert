#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <Engine/Core/Minigin.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Core/Time.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Misc/Constants.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Audio/SoundSystem.h>

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_version.h>
#include <SDL3/SDL_video.h>

#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <filesystem>
#include <ctime>
#include <functional>

#if USE_STEAMWORKS
#pragma warning (push)
#pragma warning (disable:4996)
#include <steam_api.h>
#include <steam_api_common.h>
#pragma warning (pop)
#endif

SDL_Window* g_window{};

void LogSDLVersion(const std::string& message, int major, int minor,
    int patch)
{
#if WIN32
    std::stringstream ss;
    ss << message << major << "." << minor << "." << patch << "\n";
    OutputDebugString(ss.str().c_str());
#else
    std::cout << message << major << "." << minor << "." << patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
    static_cast<GameEngine::Minigin*>(arg)->RunOneFrame();
}
#endif

// Why bother with this? Because sometimes students have a different SDL version
// installed on their pc. That is not a problem unless for some reason the dll's
// from this project are not copied next to the exe. These entries in the debug
// output help to identify that issue.
void PrintSDLVersion()
{
    LogSDLVersion("Compiled with SDL", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
        SDL_MICRO_VERSION);
    int version = SDL_GetVersion();
    LogSDLVersion("Linked with SDL ", SDL_VERSIONNUM_MAJOR(version),
        SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
    // LogSDLVersion("Compiled with SDL_image ",SDL_IMAGE_MAJOR_VERSION,
    // SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_MICRO_VERSION); version = IMG_Version();
    // LogSDLVersion("Linked with SDL_image ", SDL_VERSIONNUM_MAJOR(version),
    // SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
    LogSDLVersion("Compiled with SDL_ttf ", SDL_TTF_MAJOR_VERSION,
        SDL_TTF_MINOR_VERSION, SDL_TTF_MICRO_VERSION);
    version = TTF_Version();
    LogSDLVersion("Linked with SDL_ttf ", SDL_VERSIONNUM_MAJOR(version),
        SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
}

void GameEngine::Minigin::SetGameScreenSize(int width, int height)
{
    SDL_SetWindowSize(g_window, width, height);
    Renderer::Get().SetRenderLogicalPresentation(width, height);
}

void GameEngine::Minigin::MaximizeWindow()
{
    SDL_MaximizeWindow(g_window);
}

GameEngine::Minigin::Minigin(const std::filesystem::path& dataPath)
    : m_LastTime{ std::chrono::high_resolution_clock::now() }
    , m_Lag{ 0.f }
    , m_Quit{ false }
{
#if USE_STEAMWORKS
    if (!SteamAPI_Init())
        throw std::runtime_error(std::string("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)."));
#endif

    PrintSDLVersion();

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Renderer error: %s", SDL_GetError());
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    g_window = SDL_CreateWindow("Programming 4 assignment", Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);
    if (g_window == nullptr)
    {
        throw std::runtime_error(std::string("SDL_CreateWindow Error: ") +
            SDL_GetError());
    }
    SDL_SetWindowResizable(g_window, true);

    Renderer::Get().Init(g_window);
    ResourceManager::Get().Init(dataPath);

    ServiceLocator::Get().RegisterSoundSystem(std::make_unique<MiniAudioSoundSystem>());
}

GameEngine::Minigin::~Minigin()
{
#if USE_STEAMWORKS
    SteamAPI_Shutdown();
#endif
    Renderer::Get().Destroy();
    SDL_DestroyWindow(g_window);
    g_window = nullptr;
    SDL_Quit();
}

void GameEngine::Minigin::Run(const std::function<void()>& load)
{
    load();
#ifndef __EMSCRIPTEN__

    while (!m_Quit)
    {
        RunOneFrame();
    }
#else
    emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}

void GameEngine::Minigin::RunOneFrame()
{
    auto const currentTime{ std::chrono::high_resolution_clock::now() };
    //Time::DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
    EngineUseOnly::SetDeltaTime(std::chrono::duration<float>(currentTime - m_LastTime).count());
    m_LastTime = currentTime;

    m_Lag += GetDeltaTime();

    m_Quit = !InputManager::Get().ProcessInput();


    while (m_Lag >= GetFixedTime())
    {
        SceneManager::Get().FixedUpdate();
        m_Lag -= GetFixedTime();
    }
    SceneManager::Get().Update();
    SceneManager::Get().CheckForDeletion();

    Renderer::Get().Render();

    SceneManager::Get().CheckForSceneChange();

#if USE_STEAMWORKS
    SteamAPI_RunCallbacks();
#endif 
}
