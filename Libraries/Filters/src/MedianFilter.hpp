#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <stdint.h>
#include "Filter.hpp"

class MedianFilter : public Filter {
public:
    MedianFilter(const uint8_t sample_count);
    ~MedianFilter();
    int16_t GetFilteredSignal();

private:
};

#endif
