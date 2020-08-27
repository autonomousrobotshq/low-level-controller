#include "SensorGPS.hpp"

static bool serialInitialized;

void SensorGPS::getLocation(float* flat, float* flon)
{
    *flat = this->flat;
    *flon = this->flon;
}

float	SensorGPS::getSpeed()
{
    return(this->kmph);
}

float SensorGPS::getCourse()
{
	return(this->course);
}

void SensorGPS::getTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    *age = this->age;
    *date = this->date;
    *time = this->time;
}

bool SensorGPS::update()
{
    if (ss && ss->available()) {
        int c = ss->read();
        if (gps.encode(c)) // encode returns true if serial has received proper data
        {
            gps.f_get_position(&flat, &flon, &age);
            gps.stats(&chars, &sentences, &checksum);
            gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
            kmph = gps.f_speed_kmph();
            course = gps.f_course();
            if (age == TinyGPS::GPS_INVALID_AGE) {
                // handle invalid time info
            }
            if (flat == TinyGPS::GPS_INVALID_F_ALTITUDE) {
                // handle invalid location info
            }
            if (kmph == TinyGPS::GPS_INVALID_F_SPEED) {
                // handle invalid speed info
            }
            if (course == TinyGPS::GPS_INVALID_F_ANGLE) {
                // handle invalid course info
            }
			return (true);
        }
		else
			return (false);
    }
	else
		return (false);
}

SensorGPS::SensorGPS(const int rxPin, const int txPin)
{
    if (!serialInitialized) {
        this->ss = new SoftwareSerial(rxPin, txPin);
        serialInitialized = true;
    }
	else
		this->ss = NULL;
	
    this->update();
}

SensorGPS::~SensorGPS()
{
    delete this->ss;
}
