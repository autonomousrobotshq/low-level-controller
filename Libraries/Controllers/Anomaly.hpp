#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
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
    ControllerAnomaly();
    ~ControllerAnomaly();

	// change to clear boolean naming like IsOverheated
    bool UltraSonic(int left, int right);
    bool Heat_Warning(int8_t degr);
    bool Overheating(int8_t degr);
    bool Battery(uint8_t percentage);

	//this is a debugging option -> only check for things that we can react upon
    bool RAM(int free_space);
};

#endif
