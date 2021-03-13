#include <complex>

#include "Mandelbrot.h"

namespace IPA
{
	int Mandelbrot::getIteration(const Coord2D & scaledPos)
	{
		int iter = 0;

		std::complex<double> c(scaledPos.x, scaledPos.y);
		for (std::complex<double> z = 0; abs(z) <= 2 && iter < MAX_ITER; ++iter)
		{
			z = z * z + c;
		}
		return iter;
	}
}