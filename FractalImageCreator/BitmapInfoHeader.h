#ifndef _BITMAPINFOHEADER_H_
#define _BITMAPINFOHEADER_H_

#include <cstdint>

#pragma pack(push, 2)

namespace Bitmap 
{
	struct BitmapInfoHeader
	{
		int32_t headerSize{ 40 };				// the size of this header, in bytes (40)
		int32_t width;							// the bitmap width in pixels (signed integer)
		int32_t height;							// the bitmap height in pixels (signed integer)
		int16_t planes{ 1 };					// the number of color planes (must be 1)
		int16_t bitsPerPixel{ 24 };				// the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 32
		int32_t compression{ 0 };				// the compression method being used, by default is BI_RGB = 0, no compression
		int32_t dataSize{ 0 };					// the image size, This is the size of the raw bitmap data, a dummy 0 can be given for BI_RGB bitmaps
		int32_t horizontalResolution{ 2400 };	// the horizontal resolution of the image (pixel per metre, signed integer)
		int32_t verticalResolution{ 2400 };		// the vertical resolution of the image (pixel per metre, signed integer)
		int32_t colors{ 0 };					// the number of colors in the color palette, or 0 to default to 2^n
		int32_t importantColors{ 0 };			// the number of important colors used, or 0 when every color is important, generally ignored
	};
}

#pragma pack(pop)

#endif // !_BITMAPINFOHEADER_H_
