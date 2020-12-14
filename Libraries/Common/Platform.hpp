/*
*	Pinlayout and all platform related constants are defined here.
*	-- layout for Atmega2560/Mega
*/

#ifndef COMMON_PLATFORM_HPP
#define COMMON_PLATFORM_HPP

#include <pins_arduino.h>
#include <stdint.h>

#include "Common/Datatypes.hpp"
#include "Common/Deployment.hpp"

/*
 * LL CONTROLLER SPECIFIC CONFIGURATIONS
 * Don't use 'LLC1 or LLC2 etc. -> LLC is declared in Deployment.hpp
*/
namespace LLC1 {

/* RANGES */
#define MOTOR_THROTTLE_HIGH 100
#define MOTOR_THROTTLE_LOW 0

/* FACTS */
#define NUM_MOTORS 4
#define NUM_ULTRASONIC 4
#define NUM_RELAYS 6
#define NUM_TEMP 1

/* EXECUTION INTERVALS */
// GPS, IMU, HALL, CURRENT, TEMPERATURE, ULTRASONIC, INTERFACE_ROS
const t_exec_intervals exec_intervals = { 1000, 20, 20, 20, 1000, 20, 50};

/* IMU CALIBRATION */

// X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX
const t_imu_calibration imu_calibration_magnetometer = { -1068, +450,
    -783, +549,
    -564, +591 };
const t_imu_calibration imu_calibration_accelerometer = { -32767, 32767,
    -32767, 32767,
    -32767, 32767 };
#define IMU_SAMPLE_COUNT 3

enum e_relays {
    REL_POWER = 0,
    REL_V12 = 2,
    REL_MOTORS = 4,
    REL_FAN = 5,
};

// PWM, A, B
const t_pins_motor pins_motors[NUM_MOTORS] = {
    { 4, 23, 25 },
    { 5, 27, 29 },
    { 6, 31, 33 },
    { 7, 35, 37 }
};

// SDA, SCL
const t_pins_imu pins_imu = { 20, 21 };

// BAUDRATE, HARDWARESERIAL
const t_pins_gps pins_gps = { 9600, Serial2 };

// PIN, INTERRUPT INDEX
const t_pins_hall pins_hall[NUM_MOTORS] = {
    { 18, 0 }, // INTERRUPT INDEX NOT RESEARCHED YET
    { 19, 0 },
    { 2, 0 },
    { 3, 0 }
};

const uint8_t pins_current[NUM_MOTORS] = {
    A0,
    A1,
    A2,
    A3
};

const uint8_t pins_ultrasonic[NUM_ULTRASONIC] = {
    A4,
    A5,
    A6,
    A7
};

const uint8_t pins_relay[NUM_RELAYS] = {
    39,
    40,
    41,
    42,
    43,
    44
};

// BEEPER
const t_pins_physicalfeedback pins_physicalfeedback = { 46 };

const uint8_t pins_temp[NUM_TEMP] {
    0 // THESE PINS NEEDS TO BE RESEARCHED
};
} // namespace LLC1

#endif
