#ifndef CONTROLLER_PROXIMITY_HPP
# define CONTROLLER_PROXIMITY_HPP

#include "Sensors/Ultrasonic.hpp"

class ControllerProximity : public Controller {
	public:
		ControllerProximity();
		~ControllerProximity();
	private:
		SensorUltrasonic _ultrasonic_sensors[4];
};

#endif
