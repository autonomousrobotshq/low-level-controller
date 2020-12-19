#include "Controllers/Awareness.hpp"

ControllerAwareness::ControllerAwareness()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        _ultrasonic_sensors[i] = new SensorUltrasonic(LLC::pins_ultrasonic[i], LLC::exec_intervals.ultrasonic);
    for (int i = 0; i < NUM_TEMP; i++)
        _temperature_sensors[i] = new SensorTemp(LLC::pins_temp[i], LLC::exec_intervals.temperature);
    for (int i = 0; i < NUM_MOTORS; i++)
        _current_sensors[i] = new SensorCurrent(LLC::pins_current[i], LLC::exec_intervals.current);
}

ControllerAwareness::~ControllerAwareness()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        delete (_ultrasonic_sensors[i]);
    for (int i = 0; i < NUM_TEMP; i++)
        delete (_temperature_sensors[i]);
    for (int i = 0; i < NUM_MOTORS; i++)
        delete (_current_sensors[i]);
}

uint8_t ControllerAwareness::GetDistance(const e_corner corner)
{
    return (_ultrasonic_sensors[corner]->GetDistance());
}

uint8_t ControllerAwareness::GetTemperature(const uint8_t temp_sensor)
{
    return (_temperature_sensors[temp_sensor]->GetTemp());
}

uint8_t ControllerAwareness::GetCurrent(const e_corner corner)
{
	return (_current_sensors[corner]->GetCurrent());
}

bool ControllerAwareness::Update()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++) {
        if (_ultrasonic_sensors[i]->Update()) {
            if (_ultrasonic_sensors[i]->GetDistance() < CRITICAL_DISTANCE) {
                g_state = S_PROXIMITY_CRIT;
                return (false);
            } else if (_ultrasonic_sensors[i]->GetDistance() < DANGEROUS_DISTANCE) {
                g_state = S_PROXIMITY_WARN;
                return (false);
            }
        } else {
            g_state = S_PROXIMITY_ERROR;
            //return (false);
        }
    }
    for (int i = 0; i < NUM_TEMP; i++) {
        if (_temperature_sensors[i]->Update()) {
            if (_temperature_sensors[i]->GetTemp() > CRITICAL_TEMPERATURE) {
                g_state = S_TEMP_CRIT;
                //return (false);
            } else if (_temperature_sensors[i]->GetTemp() > DANGEROUS_TEMPERATURE) {
                g_state = S_TEMP_WARN;
                //return (false);
            }
        } else {
            g_state = S_TEMP_ERROR;
            //return (false);
        }
    }
    for (int i = 0; i < NUM_MOTORS; i++) {
	if (_current_sensors[i]->Update()) {
		if (_current_sensors[i]->GetCurrent() < CRITICAL_CURRENT) {
			g_state = S_CURRENT_CRIT;
			//return (false);
		}
	} 
	else {
		g_state = S_CURRENT_ERROR;
		//return (false);
	}
    }
    return true;
}
