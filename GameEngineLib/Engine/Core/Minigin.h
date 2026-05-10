#ifndef MINIGIN_H
#define MINIGIN_H

#include <chrono>
#include <filesystem>
#include <functional>
#include <Engine/Core/GameObject.h>

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
}

#endif