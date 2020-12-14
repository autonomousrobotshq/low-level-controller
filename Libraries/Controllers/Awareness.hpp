#ifndef CONTROLLER_AWARENESS_HPP
#define CONTROLLER_AWARENESS_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Common/State.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"

#define DANGEROUS_DISTANCE 20
#define DANGEROUS_TEMPERATURE 60
#define CRITICAL_DISTANCE 10
#define CRITICAL_TEMPERATURE 80

class ControllerAwareness : public Controller {
public:
    ControllerAwareness();
    ~ControllerAwareness();
    uint8_t GetDistance(const e_corner corner);
    uint8_t GetTemperature(const uint8_t temp_sensor);
    bool Update();

private:
    SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
    SensorTemp* _temperature_sensors[NUM_TEMP];
};

#endif
