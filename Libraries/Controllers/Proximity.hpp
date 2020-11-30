#ifndef CONTROLLER_PROXIMITY_HPP
# define CONTROLLER_PROXIMITY_HPP

#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Sensors/Ultrasonic.hpp"

class ControllerProximity : public Controller {
	public:
		ControllerProximity();
		~ControllerProximity();
	private:
		SensorUltrasonic *_ultrasonic_sensors[NUM_ULTRASONIC];
};

#endif
