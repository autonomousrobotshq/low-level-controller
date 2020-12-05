#include "Sensors/GPS.hpp"

#include "Arduino.h"

void SensorGPS::GetLocation(float* flat, float* flon)
{
	*flat = this->_flat;
	*flon = this->_flon;
}

float SensorGPS::GetSpeed()
{
	return (this->_kmph);
}

float SensorGPS::GetCourse()
{
	return (this->_course);
}

void SensorGPS::GetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
	*age = this->_age;
	*date = this->_date;
	*time = this->_time;
}

bool SensorGPS::Update()
{
	bool newData = false;
	for (unsigned long start = millis(); millis() - start < 1000;)
	{
		while(_ss.available())
		{
			char c = _ss.read();
			if (_gps.encode(c))
				newData = true;
		}
	}
	if (newData)
	{
		_gps.f_get_position(&_flat, &_flon, &_age);
			_gps.stats(&_chars, &_sentences, &_checksum);
			_gps.crack_datetime(&_year, &_month, &_day, &_hour,
					&_minute, &_second, &_hundredths, &_age);
			_kmph = _gps.f_speed_kmph();
			_course = _gps.f_course();
	}
	if (newData)
		return true;
	return false;
}

SensorGPS::SensorGPS(const t_pins_gps pins_gps)
	: _ss((HardwareSerial&)pins_gps.serial)
{
	_ss.begin(pins_gps.baudrate);
}

SensorGPS::~SensorGPS()
{
}
