#include <Arduino.h>
#include "SensorGPS.hpp"

/*
** SensorDataGPS
*/

SensorDataGPS &SensorGPS::RetreiveData()
{
	return (_data);
}

void SensorGPS::GetLocation(float* flat, float* flon)
{
    *flat = _data._flat;
    *flon = _data._flon;
}

float SensorGPS::GetSpeed()
{
    return (_data._kmph);
}

float SensorGPS::GetCourse()
{
    return (_data._course);
}

void SensorGPS::GetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    *age = _data._age;
    *date = _data._date;
    *time = _data._time;
}

#ifdef ROS
void SensorDataGPS::Publish()
{
	this->GetLocation(&_msg_gps.lat, &_msg_gps.lon);
    PublishMsg(&_msg_gps);
}
#endif

void SensorDataGPS::GetLocation(float* flat, float* flon)
{
    *flat = _flat;
    *flon = _flon;
}

float SensorDataGPS::GetSpeed()
{
    return (_kmph);
}

float SensorDataGPS::GetCourse()
{
    return (_course);
}

void SensorDataGPS::GetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    *age = _age;
    *date = _date;
    *time = _time;
}

/*
** SensorGPS
*/

SensorGPS::SensorGPS(	HardwareSerial& serial,
						const uint16_t baudrate,
						const uint16_t timeout,
						const unsigned long sampling_interval)
    : Sensor(sampling_interval)
    , _ss(serial)
	, _baudrate(baudrate)
	, _timeout(timeout)
{
}

SensorGPS::~SensorGPS()
{
}

bool SensorGPS::Init()
{
    _ss.begin(_baudrate);
	return (true);
}

bool SensorGPS::Update()
{
    if (!this->IsTimeToExecute())
        return (true);
    bool newData = false;
    for (unsigned long start = millis(); millis() - start < _timeout;) {
        while (_ss.available()) {
            char c = _ss.read();
            if (_gps.encode(c))
                newData = true;
        }
    }
    if (newData) {
        _gps.f_get_position(&_data._flat, &_data._flon, &_data._age);
        _gps.stats(&_data._chars, &_data._sentences, &_data._checksum);
        _gps.crack_datetime(&_data._year, &_data._month, &_data._day, &_data._hour,
            &_data._minute, &_data._second, &_data._hundredths, &_data._age);
        _data._kmph = _gps.f_speed_kmph();
        _data._course = _gps.f_course();
        if (_data._age == TinyGPS::GPS_INVALID_AGE) {
            // handle invalid time info
        }
        if (_data._flat == TinyGPS::GPS_INVALID_F_ALTITUDE) {
            // handle invalid location info
        }
        if (_data._kmph == TinyGPS::GPS_INVALID_F_SPEED) {
            // handle invalid speed info
        }
        if (_data._course == TinyGPS::GPS_INVALID_F_ANGLE) {
            // handle invalid course info
        }
#ifdef ROS
		if (_data.IsPublishingEnabled())
			_data.Publish();
#endif
    }
    return (true);
}

