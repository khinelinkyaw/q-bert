#ifndef MINIGIN_H
#define MINIGIN_H

#include <chrono>
#include <filesystem>
#include <functional>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include <filesystem>

namespace fs = std::filesystem;

namespace GameEngine
{
    class Minigin final
    {
    private:
        std::chrono::high_resolution_clock::time_point m_LastTime;
        float m_Lag;
        bool m_Quit;
        inline static float const m_TimeStep{ 1.f / 60.f };
        inline static float m_DeltaTime{};

    public:
        void Run(const std::function<void()>& load);
        void RunOneFrame();
        static float GetDeltaTime() { return m_DeltaTime; }
        static float GetFixedTimeStep() { return m_TimeStep; }

        static void SetGameScreenSize(int width, int height);

        explicit Minigin(const std::filesystem::path& dataPath);
        ~Minigin();
        Minigin(const Minigin& other) = delete;
        Minigin(Minigin&& other) = delete;
        Minigin& operator=(const Minigin& other) = delete;
        Minigin& operator=(Minigin&& other) = delete;
    };

    void inline RunGame(const std::function<void()>& gameLoad)
    {
#if __EMSCRIPTEN__
        fs::path data_location = "";
#else
        fs::path data_location = "./Data/";
        if (!fs::exists(data_location))
            data_location = "../Data/";
#endif
        GameEngine::Minigin engine(data_location);
        engine.Run(gameLoad);
    }
}

#endif