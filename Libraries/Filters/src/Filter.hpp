#ifndef FILTER_HPP
#define FILTER_HPP

#include <stdint.h>

class Filter {
	public:
    	Filter(const uint8_t sample_count);
    	virtual ~Filter();
    	void Reset();
    	void NewReading(const int16_t reading);
    	virtual int16_t GetFilteredSignal();
	protected:
    	int16_t* _readings;
    	uint8_t _index;
    	uint8_t _size;
};

#endif
