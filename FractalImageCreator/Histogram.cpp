#include "Histogram.h"

Histogram::Histogram(int bins) : m_bins(bins), m_histogram(new int[bins] {0})
{
}

Histogram::Histogram(const Histogram && other) : m_bins(other.m_bins), m_histogram(other.m_histogram.get())
{
}

void Histogram::increment(int bin)
{
	m_histogram[bin]++;
}

int Histogram::sum() const
{
	int count = 0;
	for (int bin = 0; bin < m_bins; ++bin)
	{
		count += m_histogram[bin];
	}
	return count;
}

const int & Histogram::operator[](int bin) const
{
	return m_histogram[bin];
}
