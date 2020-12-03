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
    bool UltraSonic(int left, int right);
    bool Heat_Warning(int8_t degr);
    bool Overheating(int8_t degr);
    bool Battery(uint8_t percantage);
    bool RAM(int free_space);
};

#endif
