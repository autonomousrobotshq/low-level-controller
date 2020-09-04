#include <Arduino.h>

#include "SensorHall.hpp"

void	SensorHall::update()
{

}

void	interruptCall(SensorHall *sh)
{
	sh->pulse++;
}

SensorHall::SensorHall(	const int _pinA,
						const int _pinB,
						const int _interrupt,
						const unsigned long *_globMillis) :
						Sensor(_globMillis),
						pinA(_pinA),
						pinB(_pinB),
						interrupt(_interrupt)
{
	pinMode(_pinB, INPUT);
	attachInterrupt(_interrupt, interruptCall, CHANGE, this);
}

SensorHall::~SensorHall()
{
	
}
