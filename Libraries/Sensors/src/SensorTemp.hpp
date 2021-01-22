#ifndef SENSOR_TEMPERATURE_HPP
#define SENSOR_TEMPERATURE_HPP

#ifndef ARDUINO_CI
# include <DallasTemperature.h>
# include <OneWire.h>
#endif

#include "Sensor.hpp"

class SensorDataTemp : public SensorData 
{
	public:
		enum error {
			TEMP_CAP_LOWER,
			TEMP_CAP_UPPER
		};
    	int16_t GetTemp();
	private:
		friend class SensorTemp;
    	int16_t _celsius = 0;
		int16_t _lower_limit = 0;
		int16_t _upper_limit = 0;

#ifdef ROS
    public:
        void Publish();
    private:
        //spine_msg::msg_temp _temp_msg;
#endif

};

class SensorTemp : public Sensor {
public:
    SensorTemp(const uint8_t pin, const unsigned long sampling_interval);
    ~SensorTemp();
	bool Init();
    bool Update();
	void SetMonitoringParameters(const uint16_t lower_limit, const uint16_t upper_limit);
    int16_t GetTemp();

private:

#ifndef ARDUINO_CI
    OneWire _wire;
    DallasTemperature _dallas;
#endif

	SensorDataTemp _data;
};

#endif
