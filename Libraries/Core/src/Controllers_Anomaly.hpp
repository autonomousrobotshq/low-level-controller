#ifndef CONTROLLER_PROXIMITY_HPP
#define CONTROLLER_PROXIMITY_HPP

#include "Common_Datatypes.hpp"
#include "Common_State.hpp"
#include "Controllers_Controller.hpp"
#include "Controllers_Lifetime.hpp"

class ControllerAnomaly {
public:
    ControllerAnomaly(void* sandbox, ControllerLifetime* controller_lifetime);
    ~ControllerAnomaly();

    bool HandleError(const e_state state);

private:
    ControllerLifetime* _controller_lifetime;
    void* _sandbox;
};

#endif
