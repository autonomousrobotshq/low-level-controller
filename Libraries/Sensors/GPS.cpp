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
	if (!this->IsTimeToExecute())
		return (true);
	bool newData = false;
	for (unsigned long start = millis(); millis() - start < GPS_TIMEOUT;)
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
		if (_age == TinyGPS::GPS_INVALID_AGE) {
			// handle invalid time info
		}
		if (_flat == TinyGPS::GPS_INVALID_F_ALTITUDE) {
			// handle invalid location info
		}
		if (_kmph == TinyGPS::GPS_INVALID_F_SPEED) {
			// handle invalid speed info
		}
		if (_course == TinyGPS::GPS_INVALID_F_ANGLE) {
			// handle invalid course info
		}
	}
	//if (newData)
	//	return (true);
	return (true);
}

SensorGPS::SensorGPS(const t_pins_gps pins_gps, const uint16_t exec_interval)
	: Sensor(exec_interval)
	, _ss((HardwareSerial&)pins_gps.serial)
{
	_ss.begin(pins_gps.baudrate);
}

SensorGPS::~SensorGPS()
{
}
