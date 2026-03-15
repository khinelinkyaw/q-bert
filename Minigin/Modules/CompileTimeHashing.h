#include <cstdint>
#ifndef COMPILETIMEHASHING_H
#define COMPILETIMEHASHING_H

namespace Engine
{
	// Copied from this blog post
	// https://dev.krzaq.cc/post/switch-on-strings-with-c11/

	typedef std::uint64_t hash_t;

	namespace Hashing
	{
		constexpr hash_t Prime = 0x100000001B3ull;
		constexpr hash_t Basis = 0xCBF29CE484222325ull;
	}

	constexpr hash_t hash_compile_time(char const* str, hash_t last_value = Hashing::Basis)
	{
		return *str ? hash_compile_time(str + 1, (*str ^ last_value) * Hashing::Prime) : last_value;
	}

	hash_t hash(char const* str)
	{
		hash_t result{ Hashing::Basis };

		while (*str)
		{
			result ^= *str;
			result *= Hashing::Prime;
			str++;
		}

		return result;
	}

	constexpr unsigned long long operator "" _hash(char const* p, size_t)
	{
		return hash_compile_time(p);
	}
}


#endif