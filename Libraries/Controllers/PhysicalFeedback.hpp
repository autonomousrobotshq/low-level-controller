#ifndef CONTROLLER_PHYSICALFEEDBACK_HPP
#define CONTROLLER_PHYSICALFEEDBACK_HPP

#include "Actuators/Beeper.hpp"
#include "Common/Datatypes.hpp"
#include "Common/State.hpp"
#include "Controllers/Controller.hpp"

#define PHYSSIG_SIG_PRE 50
#define PHYSSIG_SIG_ON 20
#define PHYSSIG_SIG_OFF 15

typedef struct s_physical_signal_format {
    uint8_t count;
    uint8_t on;
    uint8_t off;
} t_physical_signal_format;

const t_physical_signal_format physsig_format_info = { 1, 30, 30 };
const t_physical_signal_format physsig_format_warn = { 2, 30, 30 };
const t_physical_signal_format physsig_format_crit = { 3, 30, 30 };

class ControllerPhysicalFeedback : public Controller {
public:
    ControllerPhysicalFeedback(const t_pins_physicalfeedback pins_physicalfeedback);
    ~ControllerPhysicalFeedback();
    void SignalState(const e_state state);
    void Beep(const e_siglevel siglevel, const uint8_t count);

private:
    ActuatorBeeper _actuator_beeper;
};
#endif
