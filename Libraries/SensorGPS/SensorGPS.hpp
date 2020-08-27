#ifndef SENSORGPS_HPP
#define SENSORGPS_HPP

// TinyGPS documentation:
// https://github.com/neosarchizo/TinyGPS/blob/master/examples/test_with_gps_device/test_with_gps_device.ino

#include <SoftwareSerial.h>

class SensorGPS : public Sensor {
public:
    void getLocation(float* flat, float* flong);
    void getTime(unsigned long* age, unsigned long* date, unsigned long* time);
    void getSpeed(float* speed);
    void getCourse(float* course);
    void update();
    SensorGPS(const int rxPin, const int txPin);
    ~SensorGPS;

private:
    SoftwareSerial ss;
    TinyGPS gps;
    float flat, flon, kmph;
    unsigned long age, date, time, chars = 0;
    unsigned short sentences = 0, checksum = 0;
    int year;
    byte month, day, hour, minute, second, hundredths;
};

#endif
