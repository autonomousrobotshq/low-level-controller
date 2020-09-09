#ifndef SENSORGPS_HPP
#define SENSORGPS_HPP

// TinyGPS documentation:
// https://github.com/neosarchizo/TinyGPS/blob/master/examples/test_with_gps_device/test_with_gps_device.ino

#include <SoftwareSerial.h>
#include <TinyGPS.h>

#include <Sensor.hpp>

class SensorGPS : public Sensor {
public:
    void getLocation(float* flat, float* flon);
    void getTime(unsigned long* age, unsigned long* date, unsigned long* time);
    float getSpeed();
    float getCourse();
    bool update();
    SensorGPS(const int rxPin, const int txPin);
    ~SensorGPS();

private:
    SoftwareSerial* _ss;
    TinyGPS _gps;
    float _flat,
        _flon,
        _kmph,
        _course;
    unsigned long _age,
        _date,
        _time,
        _chars = 0;
    unsigned short _sentences = 0,
                   _checksum = 0;
    int _year;
    byte _month,
        _day,
        _hour,
        _minute,
        _second,
        _hundredths;
};

#endif
