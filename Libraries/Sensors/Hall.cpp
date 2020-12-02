#include <Arduino.h>

#include "Common/Platform.hpp"
#include "Sensors/Hall.hpp"

// attach interrupt doesnt allow arguments(like a 'this' argument), so hardcoded globs are required
static unsigned int pulses[NUM_MOTORS];

bool SensorHall::update()
{
    unsigned long millisDev = this->getDuration();
    this->_rpm = millisDev == 0 ? 0 : (pulses[this->_interrupt_index] / HALL_CPR) / (millisDev / 60000);
    pulses[this->_interrupt_index] = 0;
    // error handling here
    return (true);
}

int SensorHall::getRPM()
{
    return (this->_rpm);
}

static void InterruptCall0() { pulses[0]++; }
static void InterruptCall1() { pulses[1]++; }
static void InterruptCall2() { pulses[2]++; }
static void InterruptCall3() { pulses[3]++; }
static void InterruptCall4() { pulses[4]++; }
static void InterruptCall5() { pulses[5]++; }
static void InterruptCall6() { pulses[6]++; }
static void InterruptCall7() { pulses[7]++; }

SensorHall::SensorHall(const t_pins_hall pins_hall)
    : _interrupt_index(pins_hall.index_interrupt)
    , _interrupt_pin(pins_hall.pin_interrupt)

{
    pinMode(_interrupt_pin, INPUT);

    if (_interrupt_index >= NUM_MOTORS)
        return;
    switch (_interrupt_index) {
    case 0:
        attachInterrupt(_interrupt_index, InterruptCall0, CHANGE);
        break;
    case 1:
        attachInterrupt(_interrupt_index, InterruptCall1, CHANGE);
        break;
    case 2:
        attachInterrupt(_interrupt_index, InterruptCall2, CHANGE);
        break;
    case 3:
        attachInterrupt(_interrupt_index, InterruptCall3, CHANGE);
        break;
    case 4:
        attachInterrupt(_interrupt_index, InterruptCall4, CHANGE);
        break;
    case 5:
        attachInterrupt(_interrupt_index, InterruptCall5, CHANGE);
        break;
    case 6:
        attachInterrupt(_interrupt_index, InterruptCall6, CHANGE);
        break;
    case 7:
        attachInterrupt(_interrupt_index, InterruptCall7, CHANGE);
        break;
    }
}

SensorHall::~SensorHall()
{
}
