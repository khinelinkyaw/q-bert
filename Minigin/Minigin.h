#pragma once
#include <chrono>
#include <filesystem>
#include <functional>

namespace dae
{
    class Minigin final
    {
    private:
        std::chrono::high_resolution_clock::time_point m_lastTime;
        float m_lag;
        float const m_timeStep;
        bool m_quit;

    public:
        explicit Minigin(const std::filesystem::path& dataPath);
        ~Minigin();
        void Run(const std::function<void()>& load);
        void RunOneFrame();

        Minigin(const Minigin& other) = delete;
        Minigin(Minigin&& other) = delete;
        Minigin& operator=(const Minigin& other) = delete;
        Minigin& operator=(Minigin&& other) = delete;
    };
}