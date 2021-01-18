#include "ControllerMotor.hpp"

#define MIN_THROTTLE 0
#define MAX_THROTTLE 255

#define MOTOR_COUNT 2
#define M1_PIN_PWM 1
#define M1_PIN_A 2
#define M1_PIN_B 3

#define M2_PIN_PWM 4
#define M2_PIN_A 5
#define M2_PIN_B 6

enum e_side {
	LEFT,
	RIGHT
};

uint16_t acceleration_coef = 50;

const ControllerMotor::t_motor_pins pins[2] = {{ M1_PIN_PWM, M1_PIN_A, M1_PIN_B }, {M2_PIN_PWM, M2_PIN_A, M2_PIN_B }};

ControllerMotor cm(MOTOR_COUNT, pins, acceleration_coef);

void setup() {
	cm.Init();
}

void loop() {
	cm.SetAction(LEFT, ControllerMotor::FORWARD, MAX_THROTTLE);
	cm.Update();
}
