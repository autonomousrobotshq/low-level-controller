#ifndef CONTROLLER_MOTOR_HPP
#define CONTROLLER_MOTOR_HPP

#include "Actuators/Motor.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Current.hpp"
#include "Sensors/Hall.hpp"
#include "Sensors/Sensor.hpp"
#include <Arduino.h>

enum e_drive_action { // SHOULDN'T THIS BE IN Datatpes.hpp???
    FORWARD,
    BACKWARD,
    HALT,
	SLOWHALT
};

class ControllerMotor : public Controller {
public:
    ControllerMotor();
    ~ControllerMotor();

    bool IsReady();
	bool IsMoving();

	bool IsAccelerating();
	bool IsDecelerating();

	uint8_t GetThrottle(const e_side side);
	void SetThrottle(const e_side side, const uint8_t throttle);

	void SetAction(const e_side side, const e_drive_action action, const uint8_t throttle);
	void SetAction(const e_side side, const e_drive_action action);

    bool Update();

	uint8_t NormalizeThrottle(int16_t throttle);

    int8_t GetRPM(const e_corner);
    int8_t GetRevolutions(const e_corner);

private:
    ActuatorMotor* _actuators_motor[NUM_MOTOR_CONTROLLERS];
    SensorCurrent* _sensors_current[NUM_MOTORS];
    SensorHall* _sensors_hall[NUM_MOTORS];

	enum e_motorstate {
		ACCELERATING,
		DECELERATING,
		READY
	};
	e_motorstate _motorstate[NUM_MOTOR_CONTROLLERS];
    e_drive_action _action[NUM_MOTOR_CONTROLLERS];
    uint8_t _current_throttle[NUM_MOTOR_CONTROLLERS];
    uint8_t _starting_throttle[NUM_MOTOR_CONTROLLERS];
    uint8_t _desired_throttle[NUM_MOTOR_CONTROLLERS];

	unsigned long _acceleration_start_time[NUM_MOTOR_CONTROLLERS];
	uint8_t _acceleration_start_throttle[NUM_MOTOR_CONTROLLERS];

	uint8_t _acceleration_factor;

private:
	bool IsAtDesiredState(const e_side side);

	void UpdateAcceleration(const e_side side, const int8_t acceleration);
	void UpdateMotorActuator(const e_side side);
	void UpdateMotor(const e_side side);

	e_motorstate GetMotorstate(const e_side side, const uint8_t throttle);

	void SetActionParameters(const e_side side, const e_drive_action action, const uint8_t throttle);
};

#endif
