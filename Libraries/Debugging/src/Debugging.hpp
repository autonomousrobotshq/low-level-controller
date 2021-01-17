#ifndef DEBUGGING_HPP
#define DEBUGGING_HPP

#include <stdint.h>

namespace DBG {

void TimerSet();
unsigned long TimerGetMillis();
uint16_t TimerGetSeconds();

void TimerPrintMillis();
void TimerPrintSeconds();

#ifndef ARDUINO_CI
int16_t FreeRamLeft();
void PrintFreeRamLeft();
#endif

void assert(bool condition, const String &call, int linenumber);

} // namespace DBG

#endif
