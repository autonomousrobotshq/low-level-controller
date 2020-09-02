#ifndef SENSORCURRENT_HPP
#define SENSORCURRENT_HPP

#include <arduino.h>

class SensorCurrent {
public:
	float	getCurrent();
	bool	update();
	SensorCurrent(const int _analogPin);
	~SensorCurrent();
private:
	int		analogPin;
	long 	readVref();
	float	readDCCurrent(); // idem bovenstaande
	float 	Vref  = 0;
	const 	int mVperAmp = 100; // use 185 for 5A Module, and 66 for 30A Module
	float 	DCCurrent;
};

#endif
