#ifndef ACTUATOR_MOTOR_HPP
#define ACTUATOR_MOTOR_HPP

#include <stdint.h>

#include "Actuators_Actuator.hpp"
#include "Common_Datatypes.hpp"

class ActuatorMotor : public Actuator {
public:
    void Forward(const uint8_t pulse_width);
    void Reverse(const uint8_t pulse_width);
    void Halt();
    void SetThrottle(const uint8_t pulse_width);
    ActuatorMotor(const t_pins_motor pins_motor);
    ~ActuatorMotor();

private:
    const uint8_t _pin_pwm;
    const uint8_t _pin_a;
    const uint8_t _pin_b;
};

#endif
