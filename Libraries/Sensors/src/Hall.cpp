#include <Arduino.h>
#include "Hall.hpp"

// attach interrupt doesnt allow arguments(like a 'this' argument), so static globs are required
# define MAX_INTERRUPTS 8
static uint16_t pulses[MAX_INTERRUPTS];

static void InterruptCall0() { pulses[0]++; }
static void InterruptCall1() { pulses[1]++; }
static void InterruptCall2() { pulses[2]++; }
static void InterruptCall3() { pulses[3]++; }
static void InterruptCall4() { pulses[4]++; }
static void InterruptCall5() { pulses[5]++; }
static void InterruptCall6() { pulses[6]++; }
static void InterruptCall7() { pulses[7]++; }

SensorHall::SensorHall(	const uint8_t interrupt_pin,
						const uint8_t interrupt_index,
						const uint16_t counts_per_revolution,
						const uint16_t distance_per_revolution)
    : _interrupt_index((interrupt_index >= MAX_INTERRUPTS) ? MAX_INTERRUPTS - 1 : interrupt_index)
    , _interrupt_pin(interrupt_pin)
	, _counts_per_revolution(counts_per_revolution)
	, _distance_per_revolution(distance_per_revolution)
{
}

bool SensorHall::Init()
{
    pinMode(_interrupt_pin, INPUT);

    switch (_interrupt_index) {
    	case 0: attachInterrupt(_interrupt_index, InterruptCall0, CHANGE); break;
    	case 1: attachInterrupt(_interrupt_index, InterruptCall1, CHANGE); break;
    	case 2: attachInterrupt(_interrupt_index, InterruptCall2, CHANGE); break;
    	case 3: attachInterrupt(_interrupt_index, InterruptCall3, CHANGE); break;
    	case 4: attachInterrupt(_interrupt_index, InterruptCall4, CHANGE); break;
    	case 5: attachInterrupt(_interrupt_index, InterruptCall5, CHANGE); break;
    	case 6: attachInterrupt(_interrupt_index, InterruptCall6, CHANGE); break;
    	case 7: attachInterrupt(_interrupt_index, InterruptCall7, CHANGE); break;
		default: return (false);
    }
	return (true);
}

SensorHall::~SensorHall()
{
}

/*
bool SensorHall::Update()
{

	if (!IsTimeToExecute())
		return (true);
	// timed logic here 
	return (true);
}
*/

void SensorHall::CounterReset()
{
    pulses[_interrupt_index] = 0;
}

uint16_t SensorHall::CounterGetDistance()
{
    const uint16_t distance = (pulses[_interrupt_index] / _counts_per_revolution) * _distance_per_revolution;
    return (distance);
}
