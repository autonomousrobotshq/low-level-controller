#include "Controllers/Anomaly.hpp"

ControllerProximity::ControllerProximity()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        _ultrasonic_sensors[i] = new SensorUltrasonic(LLC::pins_ultrasonic[i]);
}

ControllerProximity::~ControllerProximity()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        delete _ultrasonic_sensors[i];
}

int ControllerProximity::GetDistance(const e_corner corner)
{
    return (_ultrasonic_sensors[corner]->GetDistance());
}

Anomaly::Anomaly() {}

Anomaly::~Anomaly() {}

bool Anomaly::ultrasonic(int left, int right) { return (left < ULTRASONIC_DIST or right < ULTRASONIC_DIST); }

bool Anomaly::heat_warning(int8_t degr) { return (degr >= HEAT_WARNING); }

bool Anomaly::overheating(int8_t degr){ return (degr >= OVERHEATING); }

bool Anomaly::battery(uint8_t percentage) { return (percentage <= LOW_BATTERY); }

bool Anomaly::RAM(int free_space) { return (free_space <= RAM_SPACE); }

bool Anomaly::current(float current_fl, float current_fr, float current_bl, float current_br)
{
    if (current_fl < UNDER_CURRENT or current_fl > OVER_CURRENT)
    {
        this->_error_current = current_fl;
        this->_corner_current_error = FRONT_LEFT;
        return (true);
    }
    else if (current_fr < UNDER_CURRENT or current_fr > OVER_CURRENT)
    {
        this->_error_current = current_fr;
        this->_corner_current_error = FRONT_RIGHT;
        return (true);
    }
    else if (current_bl < UNDER_CURRENT or current_bl > OVER_CURRENT)
    {
        this->_error_current = current_bl;
        this->_corner_current_error = BACK_LEFT;
        return (true);
    }
    else if (current_br < UNDER_CURRENT or current_br > OVER_CURRENT)
    {
        this->_error_current = current_br;
        this->_corner_current_error = BACK_RIGHT;
        return (true);
    }
    return false;
}

float Anomaly::get_error_current_value() const { return this->_error_current; }

e_corner Anomaly::get_error_current_corner() const { return this->_corner_current_error; }