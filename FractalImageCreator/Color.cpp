#include <math.h>

#include "Color.h"

namespace IPA
{
	namespace Color
	{
		RGB & RGB::operator*(double scale)
		{
			r = static_cast<uint8_t>(r * scale);
			g = static_cast<uint8_t>(g * scale);
			b = static_cast<uint8_t>(b * scale);

			return *this;
		}
		RGB RGB::operator*(double scale) const
		{
			uint8_t red = static_cast<uint8_t>(r * scale);
			uint8_t green = static_cast<uint8_t>(g * scale);
			uint8_t blue = static_cast<uint8_t>(b * scale);

			return RGB{ red, green, blue };
		}
		RGB RGB::operator*(const RGB & otherColor) const
		{
			uint8_t red = r * otherColor.r;
			uint8_t green = g * otherColor.g;
			uint8_t blue = b * otherColor.b;

			return RGB{ red, green, blue };
		}
		RGB RGB::pow(double magnitude) const
		{
			uint8_t red = static_cast<uint8_t>(std::pow((double)r, magnitude));
			uint8_t green = static_cast<uint8_t>(std::pow((double)g, magnitude));
			uint8_t blue = static_cast<uint8_t>(std::pow((double)b, magnitude));

			return RGB{ red, green, blue };
		}

		RGB operator+(const RGB & color1, const RGB & color2)
		{
			return RGB{
				static_cast<uint8_t>(color1.r + color2.r),
				static_cast<uint8_t>(color1.g + color2.g),
				static_cast<uint8_t>(color1.b + color2.b)
			};
		}

		RGB operator-(const RGB & color1, const RGB & color2)
		{
			return RGB{
				static_cast<uint8_t>(color1.r - color2.r),
				static_cast<uint8_t>(color1.g - color2.g),
				static_cast<uint8_t>(color1.b - color2.b)
			};
		}

		std::ostream & operator<<(std::ostream & _o, const RGB & color)
		{
			_o << "(" << color.r << ", " << color.g << ", " << color.b << ", " << ")";
			return _o;
		}
	}
}
