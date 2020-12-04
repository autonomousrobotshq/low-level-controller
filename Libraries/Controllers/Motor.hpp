#ifndef CONTROLLER_MOTOR_HPP
#define CONTROLLER_MOTOR_HPP

#include "Actuators/Motor.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Current.hpp"
#include "Sensors/Hall.hpp"
#include "Sensors/Sensor.hpp"

enum e_drive_action { // SHOULDN'T THIS BE IN Datatpes.hpp???
    FORWARD = 0,
    BACKWARD = 1,
    HALT = 2
};

class ControllerMotor : public Controller {
public:
    bool Driver(const e_side side, const e_drive_action action);
    bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle);
	bool SetThrottle();
    int8_t GetRPM(const e_corner);
	int8_t GetRevelation(const e_corner);
    bool Driver();
    bool IsReady();
    bool Update();
    ControllerMotor();
    ~ControllerMotor();

private:
    ActuatorMotor* _actuators_motor[NUM_MOTORS];
    SensorCurrent* _sensors_current[NUM_MOTORS];
    SensorHall* _sensors_hall[NUM_MOTORS];
    // e_corner _corner;
	bool _is_side[2];
    e_side _r_side;
    e_side _l_side;
    e_drive_action _action;
    uint8_t _desired_throttle;
    uint8_t _current_throttle;
};

#endif
