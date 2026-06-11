#ifndef TIMER_H
#define TIMER_H

namespace GameEngine
{
    template<typename T>
    class Timer final
    {
    private:
        bool m_IsRunning{ false };
        float m_ElapsedTime{};
        float m_Duration{};
        T m_Callback;

    private:
        bool IsDone() const { return m_ElapsedTime >= m_Duration; }
        void SetDuration(float duration) { m_Duration = duration; }
        void Update(float deltaTime);
        void Start() { m_IsRunning = true; m_ElapsedTime = 0.f; }
        void Stop() { m_IsRunning = false; }

        Timer(T callback, float duration)
            : m_Callback{ callback }
            , m_Duration{ duration }
        {
        }
    };

    template<typename T>
    inline void Timer<T>::Update(float deltaTime)
    {
        if (m_ElapsedTime < m_Duration and m_IsRunning == true)
        {
            m_ElapsedTime += deltaTime;

            if (m_ElapsedTime >= m_Duration)
            {
                m_IsRunning = false;
                m_Callback();
            }
        }
    }
}

#endif