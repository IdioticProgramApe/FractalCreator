#ifndef _FRACTAL_CREATOR_H_
#define _FRACTAL_CREATOR_H_

#include <vector>
#include <utility>

#include "Bitmap.h"
#include "Zoom.h"
#include "Mandelbrot.h"
#include "Histogram.h"
#include "Color.h"

namespace IPA
{
	struct ColorRangeInfo
	{
		Color::RGB offset;
		Color::RGB difference;
		int rangeIdx;
	};

	class FractalCreator
	{
	private:
		Bitmap m_bitmap;

		Histogram m_histogram;
		ZoomList m_zoomList;

		std::vector<int> m_iterRange;
		std::vector<Color::RGB> m_colorRange;

	public:
		FractalCreator() = delete;
		FractalCreator(int width, int height, const std::string saveDir);
		
		virtual ~FractalCreator() = default;

	public:
		/*
		* \brief
		*  Use mandelbrot algorithm to set bitmap color data
		*
		* \note
		*  dCol is a parameter allowing to shifting the mandelbrot horizontally on the image
		*/
		bool mandelbrot(const std::string & name, int dRow = 0, int dCol = 0);
	
	public:
		void addZoom(const Zoom & zoom);
		void addZoom(int row, int col, double scale);

		void addRange(double iterPrct, const Color::RGB & color);

	private:
		MandelbrotLookupTable getLookup(int dRow, int dCol);
		void writeMandelbrot(const MandelbrotLookupTable & lookUp);
		ColorRangeInfo getColorRangeInfo(int iteration) const;
	};
}

#endif // _DEBUG_FRACTAL_CREATOR_H_
