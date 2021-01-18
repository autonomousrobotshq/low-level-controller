#ifndef ACTUATOR_MOTOR_HPP
#define ACTUATOR_MOTOR_HPP

#include <stdint.h>
#include "Actuator.hpp"

class ActuatorMotor : public Actuator {
public:
    ActuatorMotor(const uint8_t pin_pwm, const uint8_t pin_a, const uint8_t pin_b);
	ActuatorMotor();
    ~ActuatorMotor();
	void SetParameters(const uint8_t pin_pwm, const uint8_t pin_a, const uint8_t pin_b);
	bool Init();
    void Forward(const uint8_t pulse_width);
    void Reverse(const uint8_t pulse_width);
    void Halt();
    void SetThrottle(const uint8_t pulse_width);

private:
    uint8_t _pin_pwm;
    uint8_t _pin_a;
    uint8_t _pin_b;
};

#endif
