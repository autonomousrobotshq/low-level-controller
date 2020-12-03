#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Ultrasonic.hpp"

class ControllerProximity : public Controller {
public:
    ControllerProximity();
    ~ControllerProximity();
    int GetDistance(const e_corner corner);

private:
    SensorUltrasonic* _ultrasonic_sensors[NUM_ULTRASONIC];
};

class Anomaly {
public:
    Anomaly();    
    ~Anomaly(); 
    bool ultrasonic(int left, int right);
    bool heat_warning(int8_t degr);
    bool overheating(int8_t degr);
    bool battery(uint8_t percentage);
    bool RAM(int free_space);
    bool current(float current_fl, float current_fr, float current_bl, float current_br);
    float get_error_current_value() const;
    e_corner get_error_current_corner() const;

private:
    float _error_current;
    e_corner _corner_current_error;
};

#endif
