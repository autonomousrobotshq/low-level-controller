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

ControllerAnomaly::ControllerAnomaly(ControllerLifetime* controller_lifetime)
    : _controller_lifetime(controller_lifetime)
{
}

ControllerAnomaly::~ControllerAnomaly() { }

bool ControllerAnomaly::HandleErrno(uint8_t errno)
{
    switch (errno) {
    case OVERHEATING_ERRNO:
        this->_controller_lifetime->Lifephase(COOLDOWN);
        // Handle errno
        break;
    case HEATWARNING_ERRNO:
        // Handle errno
        break;
    case US_PROXIMITY_ERRNO:
        // Handle errno
        break;
    case LOW_BATTERY_ERRNO:
        // Handle errno
        break;
    case OVER_CURRENT_ERRNO:
        // Handle errno
        break;
    case MOTOR_FAILURE_ERRNO:
        // Handle errno
        break;
#if VERBOSITY & DEBUG
    case LOW_RAM_ERRNO:
        // Send debug message
        break;
#endif
    default:
        return false;
        break;
    }
    return true;
}
