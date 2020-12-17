#ifndef COMMON_DEBUGGING
#define COMMON_DEBUGGING

#include <stdint.h>

namespace DBG {

void TimerSet();
unsigned long TimerGetMillis();
uint16_t TimerGetSeconds();

void TimerPrintMillis();
void TimerPrintSeconds();

int16_t FreeRamLeft();
void PrintFreeRamLeft();

} // namespace DBG

#endif
