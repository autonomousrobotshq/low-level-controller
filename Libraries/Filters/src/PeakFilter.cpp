#include <stdlib.h>
#include "PeakFilter.hpp"

PeakFilter::PeakFilter(const uint8_t sample_count)
	: Filter(sample_count)
{
}

PeakFilter::~PeakFilter()
{
}

int16_t PeakFilter::GetFilteredSignal()
{
	if (_index == 0)
		return (0);
    int16_t avg = 0;
    int16_t dev[_index + 1];
    int16_t dev_avg = 0;

    for (uint8_t i = 0; i + 1 < _index; i++) {
        dev[i] = abs(_readings[i] - _readings[i + 1]);
        dev_avg += dev[i];
    }
    dev_avg /= _index > 0 ? _index : 1;

    uint8_t number_of_qualified = 0;
    for (uint8_t i = 0; i + 1 < _index; i++) {
        if (dev[i] <= dev_avg) {
            avg += _readings[i];
            number_of_qualified++;
        }
    }
    return (number_of_qualified > 0 ? avg / number_of_qualified : _readings[0]);
}
