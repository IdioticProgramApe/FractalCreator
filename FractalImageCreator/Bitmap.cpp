#include <iostream>
#include <assert.h>
#include <fstream>

#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"


namespace IPA
{
	Bitmap::Bitmap(int width, int height, const std::string & outDir)
		: m_width(width), m_height(height)
		, m_pPixels(new uint8_t[width * height * 3] {0})  // we need a 24-bits color bitmap, and initialize to 0
		, m_root(outDir)
	{
		assert(m_pPixels && "memory for bitmap data is correctly allocated");
		if (!std::filesystem::exists(m_root))
		{
			std::filesystem::create_directories(m_root);
		}
	}

	Bitmap::Bitmap(const Bitmap && bitmap)
		: m_width(bitmap.m_width), m_height(bitmap.m_height)
		, m_pPixels(bitmap.m_pPixels.get())  // we need a 24-bits color bitmap, and initialize to 0
		, m_root(bitmap.m_root)
	{
	}

	bool Bitmap::write(const std::string & filename)
	{
		BitmapFileHeader bitmapFileHeader;
		BitmapInfoHeader bitmapInfoHeader;

		// set up for bitmap file
		auto bitmapDataSize = m_width * m_height * 3;  // unit byte
		bitmapFileHeader.fileSize = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader) + bitmapDataSize;
		bitmapFileHeader.dataOffset = sizeof(bitmapFileHeader) + sizeof(bitmapInfoHeader);

		// set up for bitmap info
		bitmapInfoHeader.width = m_width;
		bitmapInfoHeader.height = m_height;

		// set up target path
		std::filesystem::path filepath{ "." };
		std::ofstream outFile(filepath / m_root / filename, std::ios::out | std::ios::binary);
		if (!outFile)
		{
			std::cout << "Something wrong with generating a binary file" << std::endl;
			return false;
		}

		// writing...
		outFile.write((char *)&bitmapFileHeader, sizeof(bitmapFileHeader));
		outFile.write((char *)&bitmapInfoHeader, sizeof(bitmapInfoHeader));
		outFile.write((char *)m_pPixels.get(), bitmapDataSize);

		// finish writing
		outFile.close();
		if (!outFile)
		{
			std::cout << "Something wrong with closing the binary file" << std::endl;
			return false;
		}

		clear();
		return true;
	}

	void Bitmap::clear()
	{
		std::memset(m_pPixels.get(), 0, m_height * m_width * 3);
	}

	void Bitmap::setPixel(int row, int col, uint8_t red, uint8_t green, uint8_t blue)
	{
		uint8_t * curPixel = m_pPixels.get() + 3 * (row * m_width + col);

		// for one pixel, the bits order is blue, green, red, alpha
		// hex organization and memory organization is different
		curPixel[0] = blue;
		curPixel[1] = green;
		curPixel[2] = red;
	}

	void Bitmap::setRegion(int startRow, int startCol, int rowCount, int colCount, 
		uint8_t red, uint8_t green, uint8_t blue)
	{
		for (int row = startRow; row < (startRow + rowCount); ++row)
		{
			for (int col = startCol; col < (startCol + colCount); ++col)
			{
				setPixel(row, col, red, green, blue);
			}
		}
	}

	void Bitmap::setPixel(int row, int col, const Color::RGB & color)
	{
		setPixel(row, col, color.r, color.g, color.b);
	}

	void Bitmap::setRegion(int startRow, int startCol, int rowCount, int colCount, const Color::RGB & color)
	{
		setRegion(startRow, startCol, rowCount, colCount, color.r, color.g, color.b);
	}

	int Bitmap::getWidth() const
	{
		return m_width;
	}

	int Bitmap::getHeight() const
	{
		return m_height;
	}

	Bitmap::~Bitmap()
	{
	}
}

