#include <stdlib.h>
#include "Filter.hpp"

Filter::Filter(const uint8_t sample_count)
    : _index(0)
    , _size(sample_count)
{
    _readings = new int16_t[sample_count];
}

Filter::~Filter()
{
    delete[](_readings);
}

void Filter::Reset()
{
    _index = 0;
}

void Filter::NewReading(const int16_t reading)
{
	if (_index < _size)
    	_readings[_index++] = reading;
}

int16_t Filter::GetFilteredSignal()
{
	// overloaded by derived filter classes
	return (0);
}
