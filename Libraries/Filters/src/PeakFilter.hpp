#ifndef PEAKFILTER_HPP
#define PEAKFILTER_HPP

#include <stdint.h>
#include "Filter.hpp"

class PeakFilter : public Filter {
public:
    PeakFilter(const uint8_t sample_count);
    ~PeakFilter();
    int16_t GetFilteredSignal();
private:
};

#endif
