#ifndef COMMON_PEAKFILTER_HPP
#define COMMON_PEAKFILTER_HPP

#include <stdint.h>
#include "Filter.hpp"

class PeakFilter : public Filter {
public:
    PeakFilter(const uint8_t sample_count);
    ~PeakFilter();
    void Reset();
    void NewReading(const int16_t reading);
    int16_t GetFilteredSignal();

private:
    int16_t* _readings;
    uint8_t _index;
    uint8_t _size;
};

#endif
