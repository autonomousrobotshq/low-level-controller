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

ControllerAnomaly::ControllerAnomaly() { }

ControllerAnomaly::~ControllerAnomaly() { }

bool ControllerAnomaly::UltraSonic(int left, int right) { return (left < ULTRASONIC_DIST or right < ULTRASONIC_DIST); }

bool ControllerAnomaly::Heat_Warning(int8_t degr) { return (degr >= HEAT_WARNING); }

bool ControllerAnomaly::Overheating(int8_t degr) { return (degr >= OVERHEATING); }

bool ControllerAnomaly::Battery(uint8_t percantage) { return (percantage <= LOW_BATTERY); }

bool ControllerAnomaly::RAM(int free_space) { return (free_space <= RAM_SPACE); }

bool ControllerAnomaly::handle_errno(uint8_t errno)
{
    switch (errno) {
    case OVERHEATING_ERRNO:
        // Handle errno
        break ;
    case HEAT_WARNING_ERRNO:
        // Handle errno
        break ;
    case US_PROXIMITY_ERRNO:
        // Handle errno
        break ;
    case LOW_BATTERY_ERRNO:
        // Handle errno
        break ;
    case OVER_CURRENT_ERRNO:
        // Handle errno
        break ;
    case MOTOR_FAILURE_ERRNO:
        // Handle errno
        break ;
#if VERBOSITY & DEBUG
    case LOW_RAM_ERRNO:
        // Handle errno
        break ;
#endif
    default:
        break ;
    }
    return false;
}