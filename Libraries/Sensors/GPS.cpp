#include "Sensors/GPS.hpp"

static bool serialInitialized;

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
    if (_ss && _ss->available()) {
        int c = _ss->read();
        if (_gps.encode(c)) // encode returns true if serial has received proper data
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
            return (true);
        } else
            return (false);
    } else
        return (false);
}

SensorGPS::SensorGPS(const t_pins_gps& pins_gps)
    : _pin_rx(pins_gps.pin_rx)
    , _pin_tx(pins_gps.pin_tx)
{
    if (!serialInitialized) {
        this->_ss = new SoftwareSerial(_pin_rx, _pin_tx);
        serialInitialized = true;
    } else {
        this->_ss = NULL;
    }
}

SensorGPS::~SensorGPS()
{
    //delete this->_ss; // deleting object of polymorphic class type 'SoftwareSerial' which has non-virtual destructor might cause undefined behavior [-Werror=delete-non-virtual-dtor]
}
