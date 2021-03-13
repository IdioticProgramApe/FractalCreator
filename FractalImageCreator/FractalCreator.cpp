#include <assert.h>

#include "FractalCreator.h"


namespace IPA
{
	FractalCreator::FractalCreator(int width, int height, const std::string saveDir)
		: m_bitmap(width, height, saveDir)
		, m_zoomList(width, height)
		, m_histogram(Mandelbrot::MAX_ITER)
	{
		// initialized with a zoom
		addZoom(height / 2, width / 2, 4.0 / width);
	}

	MandelbrotLookupTable FractalCreator::getLookup(int dRow, int dCol)
	{
		MandelbrotLookupTable lookUp;

		for (int row = 0; row < m_bitmap.getHeight(); ++row)
		{
			// units to shift towards x-pos to see the entire Mandelbrot set
			for (int col = 0; col < m_bitmap.getWidth(); ++col)
			{
				Coord2D pos = m_zoomList.run(row - dRow, col - dCol);
				int iter = Mandelbrot::getIteration(pos);

				// recording the iterations per pixel and the histogram
				if (iter < Mandelbrot::MAX_ITER)
				{
					lookUp[std::make_pair(row, col)] = iter;
					m_histogram.increment(iter);  // store the iter to the histogram
				}
			}
		}

		return lookUp;
	}

	void FractalCreator::addZoom(const Zoom & zoom)
	{
		m_zoomList.add(zoom);
	}

	void FractalCreator::addZoom(int row, int col, double scale)
	{
		m_zoomList.add(row, col, scale);
	}

	void FractalCreator::addRange(double iterPrct, const Color::RGB & color)
	{
		m_iterRange.emplace_back(static_cast<int>(iterPrct * Mandelbrot::MAX_ITER));
		m_colorRange.emplace_back(color);
	}

	void FractalCreator::writeMandelbrot(const MandelbrotLookupTable & lookUp)
	{
		for (const auto & item : lookUp)
		{
			const int & row = item.first.first;
			const int & col = item.first.second;
			const int & iter = item.second;

			// first is colorOffset and second is colorDiff
			const auto & colorRangeInfo = getColorRangeInfo(iter);

			double hue{ 0.0 };
			for (int i = colorRangeInfo.rangeIdx; i <= iter; ++i)
			{
				hue += static_cast<double>(m_histogram[i]) / m_histogram.sum();
			}

			/// exponent mandelbrot
			Color::RGB scaledColor = colorRangeInfo.offset + colorRangeInfo.difference.pow(hue);
			/// linear mandelbrot
			//Color::RGB scaledColor = colorRangeInfo.offset + (colorRangeInfo.difference * hue);

			m_bitmap.setPixel(row, col, scaledColor);
		}
	}

	ColorRangeInfo  FractalCreator::getColorRangeInfo(int iteration) const
	{
		assert(m_iterRange.size() == m_colorRange.size());
		
		Color::RGB colorOffset, colorDiff;
		int intervalIdx, rangeIdx;

		if (iteration < m_iterRange[0])
		{
			colorOffset = Color::RGB{};
			colorDiff = m_colorRange[0] - colorOffset;
			rangeIdx = 0;
		}
		else
		{
			for (intervalIdx = 0; intervalIdx < m_iterRange.size() - 1; ++intervalIdx)
			{
				if (iteration >= m_iterRange[intervalIdx] && iteration < m_iterRange[intervalIdx + 1])
				{
					colorOffset = m_colorRange[intervalIdx];
					colorDiff = m_colorRange[intervalIdx + 1] - colorOffset;
					rangeIdx = m_iterRange[intervalIdx];
					break;
				}
			}
		}
		return ColorRangeInfo{ colorOffset, colorDiff, rangeIdx };
	}

	bool FractalCreator::mandelbrot(const std::string & name, int dRow, int dCol)
	{
		if (m_iterRange.size() == 0 || m_colorRange.size() == 0)
		{
			std::cout << "No color range provided." << std::endl;
			return false;
		}

		const auto & lookUp = getLookup(dRow, dCol);
		assert(m_histogram.sum() <= m_bitmap.getWidth() * m_bitmap.getHeight());

		writeMandelbrot(lookUp);
		return m_bitmap.write(name);
	}
}