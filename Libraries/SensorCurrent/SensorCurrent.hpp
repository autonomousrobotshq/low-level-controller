#ifndef SENSORCURRENT_HPP
#define SENSORCURRENT_HPP

#include <Arduino.h>

class SensorCurrent {
public:
    float	getCurrent();
    bool	update();
    SensorCurrent(const int analogPin);
    ~SensorCurrent();

private:
    int			_analogPin;
    long		_readVref();
    float		_readDCCurrent(); // idem bovenstaande
    float		_Vref = 0;
    const int	_mVperAmp = 100; // use 185 for 5A Module, and 66 for 30A Module
    float		_DCCurrent;
};

#endif
