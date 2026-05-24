#ifndef HEURISTICS_H
#define HEURISTICS_H

#include <cmath>
#include <algorithm>

// These are the heuristic functions from Game AI course.

namespace Game
{
	namespace HeuristicFunctions
	{
		typedef float(*Heuristic)(float, float);

		//Manhattan distance
		inline float Manhattan(float x, float y)
		{
			return x + y;
		}

		//Euclidean distance
		inline float Euclidean(float x, float y)
		{
			return sqrtf(x * x + y * y);
		}

		//Sqrt Euclidean distance
		inline float SqEuclidean(float x, float y)
		{
			return x * x + y * y;
		}

		//Octile distance
		inline float Octile(float x, float y)
		{
			float constexpr f = 0.414213562373095048801f; // == sqrt(2) - 1;
			return x < y ? f * x + y : f * y + x;
		}

		//Chebyshev distance
		inline float Chebyshev(float x, float y)
		{
			return std::max(x, y);
		}
	}
}

#endif