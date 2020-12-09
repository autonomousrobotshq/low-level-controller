#ifndef AWARENESS_HPP
#define AWARENESS_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Ultrasonic.hpp"
#include "Sensors/Temp.hpp"
#include "Common/State.hpp"

#define DANGEROUS_DISTANCE 30
#define DANGEROUS_TEMPERATURE 60
#define CRITICAL_DISTANCE 10
#define CRITICAL_TEMPERATURE 80


class Awareness : public Controller{
	public:
		Awareness();
		~Awareness();
		uint8_t GetDistance(const e_corner corner);
		uint8_t GetTemperature(const uint8_t temp_sensor);
		bool Update();

	private:
		SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
		SensorTemp* _temperature_sensors[NUM_TEMP];
};

#endif
