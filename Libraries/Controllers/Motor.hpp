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
	bool SetThrottle();
    int8_t GetRPM(const e_corner);
	int8_t GetRevelation(const e_corner);
    bool Driver();
<<<<<<< HEAD
	void SetValues(const e_corner corner, const e_drive_action action, const uint8_t throttle);
	bool IsReady();
	bool Update();
    float get_current(e_corner corner);
=======
    bool IsReady();
    bool Update();
>>>>>>> 5ce55339474a11ab83aa49ed1c92687b0465a573
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
