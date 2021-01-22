#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <stddef.h>
#include <stdlib.h>
#include "Filter.hpp"

template <typename T>
class MedianFilter : public Filter<T> {
	public:
	    MedianFilter(const size_t sample_count);
	    ~MedianFilter();
	    T GetFilteredSignal();
	private:
};

template <typename T>
MedianFilter<T>::MedianFilter(const size_t sample_count)
	: Filter<T>(sample_count)
{
}

template <typename T>
MedianFilter<T>::~MedianFilter()
{
}

template <typename T>
T MedianFilter<T>::GetFilteredSignal()
{
	if (this->_index == 0)
		return (0);
    for (size_t j = 0; j < this->_index; j++) {
        for (size_t i = 0; i < this->_index - 1 - j; i++) {
            if (this->_readings[i] > this->_readings[i + 1]) {
                T temp_value = this->_readings[i];
                this->_readings[i] = this->_readings[i + 1];
                this->_readings[i + 1] = temp_value;
            }
        }
    }
    return (this->_readings[this->_index / 2]);
}

#endif
