#ifndef ACTUATOR_MOTOR_HPP
#define ACTUATOR_MOTOR_HPP

#include <stdint.h>

#include "Actuators/Actuator.hpp"
#include "Common/Datatypes.hpp"

class ActuatorMotor : public Actuator {
public:
    void forward(const uint8_t pulse_width);
    void reverse(const uint8_t pulse_width);
    void halt();
    ActuatorMotor(const t_pins_motor pins_motor);
    ~ActuatorMotor();

private:
    const uint8_t _pinPWM;
    const uint8_t _pinA;
    const uint8_t _pinB;
};

#endif
