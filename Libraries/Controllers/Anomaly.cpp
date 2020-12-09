#include "Controllers/Anomaly.hpp"

ControllerAnomaly::ControllerAnomaly(ControllerLifetime* controller_lifetime)
    : _controller_lifetime(controller_lifetime)
{
}

ControllerAnomaly::~ControllerAnomaly() { }

bool ControllerAnomaly::HandleError(const e_state state)
{
    switch (state) {
    default:
        return (false);
    }
    return (true);
}
