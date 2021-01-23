#include <Arduino.h>
#include <Array.hpp>

const int store_size = 16;

void setup()
{
}

void loop()
{
	int backing_store[store_size];
	Array<int> myArray(backing_store);
}
