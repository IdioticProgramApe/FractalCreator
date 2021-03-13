#ifndef _ZOOM_H_
#define _ZOOM_H_

#include <vector>
#include <iostream>


namespace IPA
{
	// convert from row/col to (x, y) pair
	struct Coord2D
	{
		double x{ 0 };
		double y{ 0 };
	};

	struct Zoom
	{
		int row{ 0 };
		int col{ 0 };
		double scale{ 1.0 };

		Zoom(int r, int c, double s) :row(r), col(c), scale(s) {};
	};

	class ZoomList
	{
	private:
		int m_width{ 0 };
		int m_height{ 0 };

		double m_rowCenter{ 0.0 };
		double m_colCenter{ 0.0 };
		double m_scale{ 1.0 };

		std::vector<Zoom> m_zooms;

	public:
		ZoomList(int width, int height);
		/// move constructor
		ZoomList(const ZoomList && other);
		///
		void add(const Zoom & zoom);
		void add(int row, int col, double scale);
		///
		Coord2D run(int row, int col) const;
		///
		void print() const;

		virtual ~ZoomList() = default;

		friend std::ostream & operator<<(std::ostream & _o, const ZoomList & zoomList);
	};
}

#endif // _ZOOM_H_
