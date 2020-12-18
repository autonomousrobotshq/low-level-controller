/*
*	Generic datatypes are described here
*/

#ifndef COMMON_DATATYPES_HPP
#define COMMON_DATATYPES_HPP

#include <HardwareSerial.h>
#include <stdint.h>

enum e_side {
    LEFT,
    RIGHT,
	FRONT,
	BACK,
	ALL_SIDES
};

enum e_corner {
    FRONT_LEFT,
    FRONT_RIGHT,
    BACK_LEFT,
    BACK_RIGHT,
    ALL_CORNERS
};

enum class e_siglevel {
	DEBUG,
    INFO,
    WARN,
	ERROR,
    CRIT
};

typedef struct s_exec_intervals {
    const uint16_t gps;
    const uint16_t imu;
    const uint16_t hall;
    const uint16_t current;
    const uint16_t temperature;
    const uint16_t ultrasonic;
    const uint16_t interface_ros;
} t_exec_intervals;

typedef struct s_pins_motor {
    const uint8_t pin_pwm;
    const uint8_t pin_a;
    const uint8_t pin_b;
} t_pins_motor;

typedef struct s_pins_imu {
    const uint8_t pin_sda;
    const uint8_t pin_scl;
} t_pins_imu;

typedef struct s_pins_gps {
    const uint16_t baudrate;
    const HardwareSerial& serial;
} t_pins_gps;

typedef struct s_pins_hall {
    const uint8_t pin_interrupt;
    const uint8_t index_interrupt;
} t_pins_hall;

typedef struct s_pins_physicalfeedback {
    const uint8_t pin_beeper;
} t_pins_physicalfeedback;

typedef struct s_imu_calibration {
    const int16_t x_min;
    const int16_t x_max;
    const int16_t y_min;
    const int16_t y_max;
    const int16_t z_min;
    const int16_t z_max;
} t_imu_calibration;

#endif
