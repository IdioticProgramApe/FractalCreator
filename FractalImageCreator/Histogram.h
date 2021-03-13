#ifndef _HISTOGRAM_H_
#define _HISTOGRAM_H_

#include <memory>

class Histogram
{
private:
	int m_bins{ 0 };
	std::unique_ptr<int[]> m_histogram{ nullptr };

public:
	Histogram() = default;
	Histogram(int bins);
	/// move constructor
	Histogram(const Histogram && other);
	///
	void increment(int bin);
	///
	int sum() const;

	const int & operator[](int bin) const;

	virtual ~Histogram() = default;
};

#endif // _HISTOGRAM_H_
