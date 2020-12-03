#ifndef SENSOR_CURRENT_HPP
#define SENSOR_CURRENT_HPP

#include <Arduino.h>

class SensorCurrent {
public:
    float GetCurrent();
    bool Update();
    SensorCurrent(const uint8_t analogPin);
    ~SensorCurrent();

private:
    const uint8_t _analogPin;
    long _readVref();
    float _readDCCurrent();
    float _Vref = 0;
    const int _mVperAmp = 100; // use 185 for 5A Module, and 66 for 30A Module -> FIND THIS VARIABLE IN TESTING
    float _DCCurrent;
};

#endif
