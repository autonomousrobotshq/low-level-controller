/*
*	Generic datatypes are described here
*/

#ifndef COMMON_DATATYPES_HPP
#define COMMON_DATATYPES_HPP

#include <HardwareSerial.h>
#include <stdint.h>

enum e_side {
    LEFT_SIDE = 0,
    RIGHT_SIDE = 1,
    BOTH_SIDES = 2,
    ALL = 3
};

enum e_corner {
    FRONT_LEFT = 0,
    FRONT_RIGHT = 1,
    BACK_LEFT = 2,
    BACK_RIGHT = 3
};

enum e_relays {
    REL_POWER = 0,
    REL_V12 = 2,
    REL_MOTORS = 3,
    REL_FAN = 4,
    REL_BEEP = 6
};

enum e_lifephase {
    STARTUP,
    SHUTDOWN
};

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

#endif
