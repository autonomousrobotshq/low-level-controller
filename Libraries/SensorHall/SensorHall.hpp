#include "Sensor.hpp"

class SensorHall : public Sensor
{
	public:
		int		pulse;
		int		getRPM();
		void	update();
				SensorHall(	const int _pinA,
							const int _pinB,
							const int _interrupt,
							const unsigned long *_globMillis);
				~SensorHall();
	private:
		const int	pinA, pinB, interrupt; // interrupt corresponds to pinA! 
};
