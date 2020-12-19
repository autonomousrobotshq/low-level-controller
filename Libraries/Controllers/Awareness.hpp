#ifndef CONTROLLER_AWARENESS_HPP
#define CONTROLLER_AWARENESS_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Common/State.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/GPS.hpp"
#include "Sensors/IMU.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"
#include "Sensors/Current.hpp"

#define DANGEROUS_DISTANCE 20
#define DANGEROUS_TEMPERATURE 60
#define CRITICAL_DISTANCE 10
#define CRITICAL_TEMPERATURE 80
#define CRITICAL_CURRENT 5

class ControllerAwareness : public Controller {
public:
    ControllerAwareness();
    ~ControllerAwareness();
    uint8_t GetDistance(const e_corner corner);
    uint8_t GetTemperature(const uint8_t temp_sensor);
    uint8_t GetCurrent(const e_corner corner);
    bool Update();

	SensorGPS _sensor_gps;
	SensorIMU _sensor_imu;
private:
	// ROS stuff here too
    SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
    SensorTemp* _temperature_sensors[NUM_TEMP];
    SensorCurrent* _current_sensors[NUM_MOTORS];
private:
	void PublishData();
};

#endif
