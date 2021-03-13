#ifndef _HASH_PAIR_H_
#define _HASH_PAIR_H_

#include <utility>		// std::pair
#include <functional>   // std::hash
#include <algorithm>    // std::min

/*
* note: https://stackoverflow.com/questions/28367913/how-to-stdhash-an-unordered-stdpair
*/
template<typename T>
void hash_combine(std::size_t &seed, T const &key) 
{
	std::hash<T> hasher;
	seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
	template<typename T1, typename T2>
	struct hash<std::pair<T1, T2>>
	{
		std::size_t operator()(std::pair<T1, T2> const &p) const
		{
			std::size_t seed1(0);
			::hash_combine(seed1, p.first);
			::hash_combine(seed1, p.second);

			std::size_t seed2(0);
			::hash_combine(seed2, p.second);
			::hash_combine(seed2, p.first);

			return std::min(seed1, seed2);
		}
	};
}

#endif // _HASH_PAIR_H_
