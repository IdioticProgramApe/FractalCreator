#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <string>
#include <cstdint>
#include <memory>
#include <filesystem>  //C++17
#include <unordered_map>

#include "Color.h"


/*
* BMP file format: https://en.wikipedia.org/wiki/BMP_file_format
*/
namespace Bitmap
{
	class Bitmap
	{
	private:
		int m_width{ 0 };									// bitmap's width
		int m_height{ 0 };									// bitmap's height
		std::unique_ptr<uint8_t[]> m_pPixels{ nullptr };	// bitmap's memory pointer for pixel values

	private:
		const std::filesystem::path m_root{ "." };

	public:
		Bitmap() = default;
		Bitmap(int width, int height, const std::string & outDir);
		/// move constructor
		Bitmap(const Bitmap && bitmap);

		// bitmap file
		bool write(const std::string & filename);
		void clear();

		// bitmap info
		void setPixel(int row, int col, uint8_t red, uint8_t green, uint8_t blue);
		void setRegion(int startRow, int startCol, int rowCount, int colCount, 
			uint8_t red, uint8_t green, uint8_t blue);

		void setPixel(int row, int col, const Color::RGB & color);
		void setRegion(int startRow, int startCol, 
			int rowCount, int colCount, const Color::RGB & color);

		int getWidth() const;
		int getHeight() const;

		virtual ~Bitmap();
	};
}

#endif // _BITMAP_H_
