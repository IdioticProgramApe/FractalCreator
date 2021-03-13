#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

#include <unordered_map>
#include <utility>

#include "Zoom.h"
#include "HashPair.h"

namespace IPA
{
	typedef std::unordered_map<std::pair<int, int>, int, std::hash<std::pair<int, int>>> MandelbrotLookupTable;

	/*
	* algorithm: https://en.wikipedia.org/wiki/Mandelbrot_set
	*/
	class Mandelbrot
	{
	public:
		// trade-off between runtime and quality
		static constexpr int MAX_ITER = 1000;

	public:
		Mandelbrot() = default;
		virtual ~Mandelbrot() = default;

		static int getIteration(const Coord2D & scaledPos);
	};
}


#endif // _MANDELBROT_H_
