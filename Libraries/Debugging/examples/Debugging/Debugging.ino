#include "Debugging.hpp"

void setup() {
}

void loop() {
	unsigned long time;

	// timing
	DBG::TimerSet();
	delay(500);
	time = DBG::TimerGetMillis(); // time should be 500
	if (time > 100)
	{
		// do something if more than 100 milliseconds have passed since TimerSet()
	}
	DBG::TimerPrintMillis();
	DBG::TimerPrintSeconds();

	// ram
	int16_t ram_left;

	ram_left = DBG::FreeRamLeft();
	if (ram_left < 100)
	{
		// do something if less than 100 bytes remain
	}
	DBG::PrintFreeRamLeft();

	// assertions : if assertion fails, Arduino will hang indefinitely so use with caution!
	bool var = false;
	DBG::assert(var, __func__, __LINE__); // __func__ and __LINE__ are builtin CPP macros replaced by function name and line number 
}
