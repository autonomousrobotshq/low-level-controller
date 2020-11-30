#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Ultrasonic.hpp"

class ControllerProximity : public Controller {
public:
    ControllerProximity();
    ~ControllerProximity();
    int GetDistance(e_corner corner);

private:
    SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
};

#endif
