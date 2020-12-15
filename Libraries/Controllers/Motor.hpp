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
    bool SetThrottle(const e_side side, bool halt = false);
    bool DriverIsReady();
	bool DriverIsMoving();
	bool DriverIsAccelerating();
	bool DriverIsDecelerating();
	bool SlowHalt();
	uint8_t DriverGetThrottle();
	void DriverSetThrottle(const e_side side, const uint8_t throttle);
	bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle);
	bool Driver(const e_side side, const e_drive_action action);
    int8_t GetRPM(const e_corner);
    int8_t GetRevolutions(const e_corner);
    bool Driver();
    bool IsReady(const e_side side);
    bool Update();
    ControllerMotor();
    ~ControllerMotor();

private:
    ActuatorMotor* _actuators_motor[NUM_MOTORS];
    SensorCurrent* _sensors_current[NUM_MOTORS];
    SensorHall* _sensors_hall[NUM_MOTORS];
    // e_corner _corner;
    bool _is_side[3];
    e_drive_action _action[3];
    uint8_t _desired_throttle[3];
    uint8_t _current_throttle[3];
	uint16_t _acceleration_step[3];
	unsigned long _acceleration_time[3];
};

#endif
