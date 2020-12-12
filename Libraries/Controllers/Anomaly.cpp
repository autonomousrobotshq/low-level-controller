#include "Common/State.hpp"
#include "Controllers/Anomaly.hpp"
#include "Sandbox/Sandbox.hpp"

ControllerAnomaly::ControllerAnomaly(void *sandbox, ControllerLifetime* controller_lifetime)
    : _controller_lifetime(controller_lifetime)
	, _sandbox(sandbox)
{
}

ControllerAnomaly::~ControllerAnomaly() { }

bool ControllerAnomaly::HandleError(const e_state state)
{
    switch (state) {
	case S_PROXIMITY_CRIT:
		((sb::Sandbox *)_sandbox)->DriverHalt();
		((sb::Sandbox *)_sandbox)->SIGBeep(SIG_CRIT, 5);
	break;
	case S_PROXIMITY_WARN:
		((sb::Sandbox *)_sandbox)->DriverSlowHalt();
		((sb::Sandbox *)_sandbox)->SIGBeep(SIG_CRIT, 5);
	break;
		
    default:
        return (true); // should return false on default
    }
	g_state = S_OK;
    return (true);
}
