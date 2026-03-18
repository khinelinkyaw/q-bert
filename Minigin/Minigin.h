#ifndef MINIGIN_H
#define MINIGIN_H

#include <chrono>
#include <filesystem>
#include <functional>

namespace GameEngine
{
    namespace Constants
    {
        int const WINDOW_WIDTH{ 1024 };
        int const WINDOW_HEIGHT{ 576 };
    }

    class Minigin final
    {
    private:
        std::chrono::high_resolution_clock::time_point m_LastTime;
        float m_Lag;
        float const m_TimeStep;
        bool m_Quit;
        inline static float m_DeltaTime{};
    public:
        void Run(const std::function<void()>& load);
        void RunOneFrame();
        static float GetDeltaTime() { return m_DeltaTime; }

        explicit Minigin(const std::filesystem::path& dataPath);
        ~Minigin();
        Minigin(const Minigin& other) = delete;
        Minigin(Minigin&& other) = delete;
        Minigin& operator=(const Minigin& other) = delete;
        Minigin& operator=(Minigin&& other) = delete;
    };
}

#endif