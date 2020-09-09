#ifndef SENSORTEMP_HPP
#define SENSORTEMP_HPP

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8
// OneWire test(ONE_WIRE_BUS);
// DallasTemperature sensors(&test);

class SensorTemp{
public:
	SensorTemp(const int);
	~SensorTemp();
private:
	OneWire 			Wire = 0;
	DallasTemperature 	sensors = &Wire;
	float 				Celsius = 0;
	float				getTemp();
	float				readTempC();
	bool				update();
};
#endif