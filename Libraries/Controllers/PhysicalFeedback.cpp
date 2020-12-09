#include "Arduino.h"
#include "Controllers/PhysicalFeedback.hpp"

void	ControllerPhysicalFeedback::SignalState(const e_state state)
{
	e_siglevel siglevel;
	uint8_t count;

	switch (state)
	{
		case S_STARTUP:
			siglevel = SIG_INFO;
		break;
		case S_SHUTDOWN:
			siglevel = SIG_INFO;
		break;
		default:
			siglevel = SIG_WARN;
		break;
	}
	count = state;
	Beep(siglevel, count);
}

void	ControllerPhysicalFeedback::Beep(const e_siglevel siglevel, const uint8_t count)
{
	t_physical_signal_format signal_format;

	switch (siglevel)
	{
		case SIG_INFO:
				signal_format = physsig_format_info;
		break;
		case SIG_WARN:
				signal_format = physsig_format_warn;
		break;
		case SIG_CRIT:
				signal_format = physsig_format_crit;
		default:
				signal_format = physsig_format_warn;
		break;
	}

	for (uint8_t i = 0; i < signal_format.count; i++)
	{
		_actuator_beeper.SetState(true);
		delay(signal_format.on);
		_actuator_beeper.SetState(false);
		delay(signal_format.off);
	}

	delay(PHYSSIG_SIG_PRE);

	for (uint8_t i = 0; i < count; i++)
	{
		_actuator_beeper.SetState(true);
		delay(PHYSSIG_SIG_ON);
		_actuator_beeper.SetState(false);
		delay(PHYSSIG_SIG_OFF);
	}
}

ControllerPhysicalFeedback::ControllerPhysicalFeedback(const t_pins_physicalfeedback pins_physicalfeedback)
		: _actuator_beeper(pins_physicalfeedback.pin_beeper)
{
	
}

ControllerPhysicalFeedback::~ControllerPhysicalFeedback()
{

}
