#ifndef COMPILETIMEHASHING_H
#define COMPILETIMEHASHING_H

#include <cstdint>

namespace
{
	// Used code from this blog post
	// https://dev.krzaq.cc/post/switch-on-strings-with-c11/

	//typedef std::uint64_t hash_t;
	namespace Hashing
	{
		constexpr std::uint64_t Prime = 0x100000001B3ull;
		constexpr std::uint64_t Basis = 0xCBF29CE484222325ull;
	}

	constexpr std::uint64_t HashCompileTime(char const* str, std::uint64_t last_value = Hashing::Basis)
	{
		return *str ? HashCompileTime(str + 1, (*str ^ last_value) * Hashing::Prime) : last_value;
	}

	std::uint64_t HashString(char const* str)
	{
		std::uint64_t result{ Hashing::Basis };

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
		return HashCompileTime(p);
	}
}

#endif
