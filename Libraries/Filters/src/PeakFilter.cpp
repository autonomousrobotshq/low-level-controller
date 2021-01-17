#include "PeakFilter.hpp"
#include <stdlib.h>

PeakFilter::PeakFilter(const uint8_t sample_count)
    : _index(0)
    , _size(sample_count)
{
    _readings = new int16_t[sample_count];
}

PeakFilter::~PeakFilter()
{
    delete[](_readings);
}

void PeakFilter::Reset()
{
    _index = 0;
}

void PeakFilter::NewReading(const int16_t reading)
{
	if (_index < _size)
    	_readings[_index++] = reading;
}

int16_t PeakFilter::GetFilteredSignal()
{
    int16_t _avg = 0;
    int16_t dev[_index + 1];
    int16_t _dev_avg = 0;

    for (uint8_t i = 0; i + 1 < _index; i++) {
        dev[i] = abs(_readings[i] - _readings[i + 1]);
        _dev_avg += dev[i];
    }
    _dev_avg /= _index > 0 ? _index : 1;

    uint8_t _number_of_qualified = 0;
    for (uint8_t i = 0; i + 1 < _index; i++) {
        if (dev[i] <= _dev_avg) {
            _avg += _readings[i];
            _number_of_qualified++;
        }
    }
    return (_number_of_qualified > 0 ? _avg / _number_of_qualified : _readings[0]);
}
