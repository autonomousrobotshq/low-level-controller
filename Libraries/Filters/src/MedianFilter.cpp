#include "MedianFilter.hpp"
#include <stdlib.h>

MedianFilter::MedianFilter(const uint8_t sample_count)
	: Filter(sample_count)
{
}

MedianFilter::~MedianFilter()
{
}

int16_t MedianFilter::GetFilteredSignal()
{
	if (_index == 0)
		return (0);
    for (int j = 0; j < _index; j++) {
        for (int i = 0; i < _index - 1 - j; i++) {
            if (_readings[i] > _readings[i + 1]) {
                int16_t temp_value = _readings[i];
                _readings[i] = _readings[i + 1];
                _readings[i + 1] = temp_value;
            }
        }
    }
    return (_readings[_index / 2]);
}
