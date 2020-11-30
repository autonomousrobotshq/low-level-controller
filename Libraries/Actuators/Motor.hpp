#ifndef ACTUATOR_MOTOR_HPP
#define ACTUATOR_MOTOR_HPP

#include <stdint.h>

#include "Actuators/Actuator.hpp"

class ActuatorMotor : public Actuator {
public:
    void forward(const uint8_t pulse_width);
    void reverse(const uint8_t pulse_width);
    void halt();
    ActuatorMotor(const uint8_t pinPWM,
        const uint8_t pinA,
        const uint8_t pinB);
    ~ActuatorMotor();

private:
    const uint8_t _pinPWM;
    const uint8_t _pinA;
    const uint8_t _pinB;
};

#endif
