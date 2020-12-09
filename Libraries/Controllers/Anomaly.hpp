#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common/Datatypes.hpp"
#include "Common/State.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/Lifetime.hpp"

class ControllerAnomaly {
public:
    ControllerAnomaly(ControllerLifetime* controller_lifetime);
    ~ControllerAnomaly();

    bool HandleError(const e_state state);

private:
    ControllerLifetime* _controller_lifetime;
};

#endif
