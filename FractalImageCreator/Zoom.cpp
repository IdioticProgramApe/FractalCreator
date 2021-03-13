#include <utility>

#include "Zoom.h"


namespace Bitmap
{
	ZoomList::ZoomList(int width, int height) : m_width(width), m_height(height)
	{
		print();
	}

	ZoomList::ZoomList(const ZoomList && other)
		: m_width(other.m_width)
		, m_height(other.m_height)
		, m_zooms(std::move(other.m_zooms))
	{
	}

	void ZoomList::add(const Zoom & zoom)
	{
		m_zooms.emplace_back(zoom);

		m_rowCenter += (m_height / 2 - zoom.row) * m_scale;
		m_colCenter += (zoom.col - m_width / 2) * m_scale;
		m_scale *= zoom.scale;

		print();
	}

	void ZoomList::add(int row, int col, double scale)
	{
		m_zooms.emplace_back(Zoom(row, col, scale));

		m_rowCenter += (m_height / 2 - row) * m_scale;
		m_colCenter += (col - m_width / 2) * m_scale;
		m_scale *= scale;

		print();
	}

	Coord2D ZoomList::run(int row, int col) const
	{
		double scaledRow = (row - m_height / 2) * m_scale + m_rowCenter;
		double scaledCol = (col - m_width / 2) * m_scale + m_colCenter;

		return Coord2D{ scaledCol, scaledRow };
	}

	void ZoomList::print() const
	{
		std::cout << "Current zoom information: " << *this << std::endl;
	}

	std::ostream & operator<<(std::ostream & _o, const ZoomList & zoomList)
	{
		 _o << "(" << zoomList.m_rowCenter << ", " << 
			 zoomList.m_colCenter << ", " << 
			 zoomList.m_scale << ")";
		 return _o;
	}
}


