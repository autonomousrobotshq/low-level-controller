#ifndef CONTROLLER_MOTOR_HPP
#define CONTROLLER_MOTOR_HPP

#include "Actuators/Motor.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Current.hpp"
#include "Sensors/Hall.hpp"

enum e_drive_action { FORWARD,
    BACKWARD,
    HALT };

class ControllerMotor : public Controller {
public:
    bool Driver(e_corner corner, e_drive_action action);
    ControllerMotor();
    ~ControllerMotor();

private:
    ActuatorMotor* _actuators_motor[NUM_MOTORS];
    SensorCurrent* _sensors_current[NUM_MOTORS];
    SensorHall* _sensors_hall[NUM_MOTORS];
};

#endif
