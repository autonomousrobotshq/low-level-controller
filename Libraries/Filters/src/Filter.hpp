#ifndef FILTER_HPP
#define FILTER_HPP

#include <stddef.h>

template <typename T>
class Filter {
	public:
    	Filter(const size_t sample_count);
    	virtual ~Filter();
    	void Reset();
    	void NewReading(const T reading);
    	virtual T GetFilteredSignal();
	protected:
    	T* _readings;
    	size_t _index;
    	size_t _size;
};

template <typename T>
Filter<T>::Filter(const size_t sample_count)
    : _index(0)
    , _size(sample_count)
{
    _readings = new T[sample_count];
}

template <typename T>
Filter<T>::~Filter()
{
    delete[](_readings);
}

template <typename T>
void Filter<T>::Reset()
{
    _index = 0;
}

template <typename T>
void Filter<T>::NewReading(const T reading)
{
	if (_index < _size)
    	_readings[_index++] = reading;
}

template <typename T>
T Filter<T>::GetFilteredSignal()
{
	// overloaded by derived filter classes
	return (T(0));
}

#endif
