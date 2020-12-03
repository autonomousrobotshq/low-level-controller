#ifndef CONTROLLER_MOTOR_HPP
#define CONTROLLER_MOTOR_HPP

#include "Actuators/Motor.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Current.hpp"
#include "Sensors/Hall.hpp"
#include "Sensors/Sensor.hpp"

enum e_drive_action {
    FORWARD = 0,
    BACKWARD = 1,
    HALT = 2
};

class ControllerMotor : public Controller {
public:
    bool Driver(const e_corner corner, const e_drive_action action);
    bool Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle);
    int8_t GetRPM(const e_corner);
    bool Driver();
    bool IsReady();
    bool Update();
    ControllerMotor();
    ~ControllerMotor();

private:
    ActuatorMotor* _actuators_motor[NUM_MOTORS];
    SensorCurrent* _sensors_current[NUM_MOTORS];
    SensorHall* _sensors_hall[NUM_MOTORS];
    e_corner _corner;
    e_drive_action _action;
    uint8_t _desired_throttle;
    uint8_t _current_throttle;
};

#endif
