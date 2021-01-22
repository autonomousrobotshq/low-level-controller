#ifndef PEAKFILTER_HPP
#define PEAKFILTER_HPP

#include <stddef.h>
#include <stdlib.h>
#include "Filter.hpp"

template <typename T>
class PeakFilter : public Filter<T> {
	public:
	    PeakFilter(const size_t sample_count);
	    ~PeakFilter();
	    T GetFilteredSignal();
	private:
};

template <typename T>
PeakFilter<T>::PeakFilter(const size_t sample_count)
	: Filter<T>(sample_count)
{
}

template <typename T>
PeakFilter<T>::~PeakFilter()
{
}

template <typename T>
T PeakFilter<T>::GetFilteredSignal()
{
	if (this->_index == 0)
		return (0);
    T avg = 0;
    T dev[this->_index + 1];
    T dev_avg = 0;

    for (size_t i = 0; i + 1 < this->_index; i++) {
        dev[i] = abs(this->_readings[i] - this->_readings[i + 1]);
        dev_avg += dev[i];
    }
    dev_avg /= this->_index > 0 ? this->_index : 1;

    size_t number_of_qualified = 0;
    for (size_t i = 0; i + 1 < this->_index; i++) {
        if (dev[i] <= dev_avg) {
            avg += this->_readings[i];
            number_of_qualified++;
        }
    }
    return (number_of_qualified > 0 ? avg / number_of_qualified : this->_readings[0]);
}

#endif
