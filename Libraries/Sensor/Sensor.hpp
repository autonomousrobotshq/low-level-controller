#ifndef SENSOR_HPP
#define SENSOR_HPP

class Sensor {
public:
    unsigned long getDuration();
    Sensor(const unsigned long* _globMillis);
    Sensor();
    ~Sensor();

private:
    const unsigned long* globMillis;
};

#endif
