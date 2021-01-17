#include <Arduino.h>
#include "Debugging.hpp"

#ifndef ARDUINO_CI
# include <MemoryFree.h>
#endif

namespace DBG {

static unsigned long g_timer;

void TimerSet()
{
    g_timer = millis();
}

unsigned long TimerGetMillis()
{
    return (millis() - g_timer);
}

uint16_t TimerGetSeconds()
{
    return ((millis() - g_timer) / 1000);
}

void TimerPrintMillis()
{
    Serial.print("Time elapsed : ");
    Serial.print(millis() - g_timer);
    Serial.println(" milliseconds");
}

void TimerPrintSeconds()
{
    Serial.print("Time elapsed : ");
    Serial.print((millis() - g_timer) / 1000);
    Serial.println(" seconds");
}

#ifndef ARDUINO_CI
int16_t FreeRamLeft()
{
    return (freeMemory());
}

void PrintFreeRamLeft()
{
    Serial.print("Free RAM left : ");
    Serial.println(freeMemory());
}
#endif

void assert(bool condition, const String &call, int linenumber)
{
	if (!condition)
	{
		Serial.print("Assertion failed: ");
		Serial.print(call);
		Serial.print(" on line: ");
		Serial.println(linenumber);
		while(true) {};
	}
}

} // namespace DBG
