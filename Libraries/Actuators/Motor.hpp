#ifndef ACTUATOR_MOTOR_HPP
#define ACTUATOR_MOTOR_HPP

#include "Actuators/Actuator.hpp"

class ActuatorMotor : public Actuator {
public:
    void forward(const byte pulse_width);
    void reverse(const byte pulse_width);
    void halt();
    ActuatorMotor(const byte pinPWM,
        const byte pinA,
        const byte pinB);
    ~ActuatorMotor();

private:
    const byte _pinPWM;
    const byte _pinA;
    const byte _pinB;
};

#endif
