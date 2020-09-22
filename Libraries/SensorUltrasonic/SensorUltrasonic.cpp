#include "SensorUltrasonic.hpp"

SensorUltrasonic::SensorUltrasonic(const int pin)
	: _analogPin(pin) 
{ 
	this->update();
}

SensorUltrasonic::~SensorUltrasonic() { }

bool SensorUltrasonic::update() {
	
	_sensity_t = analogRead(_analogPin);

	_dist_t = _sensity_t * MAX_RANGE / ADC_SOLUTION;

	/*
	**	No error handling implemented yet (if at all necessary).
	*/

	return (true);
}

float SensorUltrasonic::getDistance() {
	return (_dist_t);
}
