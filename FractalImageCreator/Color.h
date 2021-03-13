#ifndef _COLOR_H_
#define _COLOR_H_

#include <cstdint>
#include <limits>
#include <iostream>

namespace IPA
{
	namespace Color
	{
		struct RGB
		{
			uint8_t r{ 0 };
			uint8_t g{ 0 };
			uint8_t b{ 0 };

			RGB & operator*(double scale);
			RGB operator*(double scale) const;
			RGB operator*(const RGB & otherColor) const;
			RGB pow(double magnitude) const;
		};

		RGB operator+(const RGB & color1, const RGB & color2);
		RGB operator-(const RGB & color1, const RGB & color2);
		std::ostream & operator<<(std::ostream & _o, const RGB & color);

		//some basic colors
		constexpr Color::RGB BLACK{ 0,   0,   0 };
		constexpr Color::RGB RED{ 255,   0,   0 };
		constexpr Color::RGB LIME{ 0, 255,   0 };
		constexpr Color::RGB BLUE{ 0,   0, 255 };
		constexpr Color::RGB YELLOW{ 255, 255,   0 };
		constexpr Color::RGB MAGENTA{ 255,   0, 255 };
		constexpr Color::RGB CYAN{ 0, 255, 255 };
		constexpr Color::RGB WHITE{ 255, 255, 255 };

		constexpr Color::RGB GRAY{ 128, 128, 128 };
		constexpr Color::RGB MAROON{ 128,   0,   0 };
		constexpr Color::RGB GREEN{ 0, 128,   0 };
		constexpr Color::RGB NAVY{ 0,   0, 128 };
		constexpr Color::RGB OLIVE{ 128, 128,   0 };
		constexpr Color::RGB PURPLE{ 128,   0, 128 };
		constexpr Color::RGB TEAL{ 0, 128, 128 };
		constexpr Color::RGB SILVER{ 192, 192, 192 };
	}
}

#endif // _COLOR_H_
