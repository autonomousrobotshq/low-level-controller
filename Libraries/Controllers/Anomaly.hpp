#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common/Datatypes.hpp"
#include "Common/Errno.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/Lifetime.hpp"
#include "Sensors/Ultrasonic.hpp"

// should the MotorController class hold ownership over the ultrasonic sensor?
class ControllerProximity : public Controller {
public:
    ControllerProximity();
    ~ControllerProximity();
    int GetDistance(const e_corner corner);

private:
    SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
};

class ControllerAnomaly {
public:
    ControllerAnomaly(ControllerLifetime* controller_lifetime);
    ~ControllerAnomaly();

    bool HandleErrno(uint8_t errno);

private:
    ControllerLifetime* _controller_lifetime;
};

#endif
