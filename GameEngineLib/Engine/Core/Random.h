#ifndef MINIGIN_RANDOM_H
#define MINIGIN_RANDOM_H

#include <chrono>
#include <random>

namespace GameEngine::Random
{
    inline std::mt19937_64& GetRNG()
    {
        static std::mt19937_64 rng{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
        return rng;
    }
}

#endif