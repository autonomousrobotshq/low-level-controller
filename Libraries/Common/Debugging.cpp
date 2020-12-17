#include "Common/Debugging.hpp"
#include <Arduino.h>
#include <MemoryFree.h>

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

int16_t FreeRamLeft()
{
    return (freeMemory());
}

void PrintFreeRamLeft()
{
    Serial.print("Free RAM left : ");
    Serial.println(freeMemory());
}

} // namespace DBG
