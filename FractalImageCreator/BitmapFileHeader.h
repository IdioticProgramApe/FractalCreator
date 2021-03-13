#ifndef _BITMAPFILEHEADER_H_
#define _BITMAPFILEHEADER_H_

#include <cstdint>

#pragma pack(push, 2)

namespace IPA
{
	struct BitmapFileHeader
	{
		char header[2]{ 'B', 'M' }; // the header field used to identify the BMP and DIB file is 0x42 0x4D, same as BM in ASCII
		int32_t fileSize;			// the size of the BMP file in bytes
		int32_t reserved{ 0 };		// 4 bytes, reserved, actual value depends on the application that creates the image, if created manually can be 0
		int32_t dataOffset;			// the offset, i.e. starting address, of the byte where the bitmap image data (pixel array) can be found
	};
}

#pragma pack(pop)

#endif // !_BITMAPFILEHEADER_H_

