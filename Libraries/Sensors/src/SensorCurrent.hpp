#ifndef SENSOR_CURRENT_HPP
#define SENSOR_CURRENT_HPP

#include "Sensor.hpp"
#include "MedianFilter.hpp"

class SensorCurrent : public Sensor {
public:
    SensorCurrent(const uint8_t analogPin, const uint8_t sample_count, const unsigned long sampling_interval);
    ~SensorCurrent();
	bool Init();
    bool Update();
    uint16_t GetCurrentMilliAmps();
    uint8_t GetCurrentAmps();
private:
    const uint8_t _analogPin;
	MedianFilter _filter;
	const uint8_t _sample_count;

 	// use 185 for 5A Module, and 66 for 30A Module -> Trial by error testing.
    const static int _mVperAmp = 100;
    long  ReadReferenceVoltage();
    uint16_t ReadDCCurrent();
    float _vref = 0;
    uint16_t _current;
};

#endif
