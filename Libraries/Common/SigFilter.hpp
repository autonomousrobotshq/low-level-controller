#ifndef COMMON_SIGFILTER_HPP
# define COMMON_SIGFILTER_HPP

#include <stdint.h>

class SigFilter {
	public:
		SigFilter(const uint8_t sample_count);
		~SigFilter();
		void	Reset();
		void	NewReading(const int16_t reading);
		int16_t GetFilteredAverage();
	private:
		int16_t *_readings;
		uint8_t _index;
		uint8_t _size;
};

#endif
