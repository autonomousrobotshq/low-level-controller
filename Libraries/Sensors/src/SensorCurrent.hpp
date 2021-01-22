#ifndef SENSOR_CURRENT_HPP
#define SENSOR_CURRENT_HPP

#include "Sensor.hpp"
#include "MedianFilter.hpp"

class SensorCurrentData : public SensorData {
	public:
		uint8_t GetCurrentAmps();
		uint16_t GetCurrentMilliAmps();
	private:
		uint16_t _current;
		friend class SensorCurrent;
#ifdef ROS
	public:
		void Publish();
	private:
		//spine_msg::msg_current _current_msg;
#endif
};

class SensorCurrent : public Sensor {
public:
    SensorCurrent(const uint8_t analogPin, const uint8_t sample_count, const unsigned long sampling_interval);
    ~SensorCurrent();
	bool Init();
    bool Update();
	SensorCurrentData &RetreiveData();
private:
    const uint8_t _analogPin;
	MedianFilter<uint16_t> _filter;
	const uint8_t _sample_count;

    const static int _mVperAmp = 100; // use 185 for 5A Module, and 66 for 30A Module -> Trial by error testing.
    long  ReadReferenceVoltage();
    uint16_t ReadDCCurrent();
    float _vref = 0;

	SensorCurrentData _data;
};

#endif
