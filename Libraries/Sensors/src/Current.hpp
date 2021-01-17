#ifndef SENSOR_CURRENT_HPP
#define SENSOR_CURRENT_HPP

#include "Sensor.hpp"

class SensorCurrent : public Sensor {
public:
    float GetCurrent();
    bool Update();
    SensorCurrent(const uint8_t analogPin, const uint16_t exec_interval);
    ~SensorCurrent();

private:
    const uint8_t _analogPin;
    long _readVref();
    float _readDCCurrent();
    float _Vref = 0;
    const static int _mVperAmp = 100; // use 185 for 5A Module, and 66 for 30A Module -> Trial by error testing.
    float _DCCurrent;
};

#endif
