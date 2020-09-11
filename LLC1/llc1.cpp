#include "llc1.hpp"

/*
** SAMPLE CODE (for now) : do not upload without verifying libraries and ports!
*/

static unsigned long globMillis;

int main(void)
{
    SensorGPS sg(3, 4);
	SensorHall(15, 16, 0, 16, &globMillis);
    SensorCurrent(5);
    SensorTemp(8);
}
