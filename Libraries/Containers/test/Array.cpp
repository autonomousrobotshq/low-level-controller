#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include <climits>
#include "Array.hpp"

unittest(Basics)
{
	const int max_size = 128;
	Array<int> Arr(max_size);

	for (size_t i = 0; i < max_size; i++) {
		Arr[i] = i;
		assertEqual(Arr[i], i);
	}
}

unittest(UnderlyingData)
{
	const int max_size = 128;
	Array<int> Arr(max_size);

	for (size_t i = 0; i < max_size; i++) {
		Arr[i] = i;
	}

	int *int_ptr = Arr.data();
	for (size_t i = 0; i < max_size; i++) {
		assertEqual(int_ptr[i], i);
	}
}

unittest(ExternalStore)
{
	const int max_size = 128;
	int store[max_size];

	Array<int> Arr(store);

	for (size_t i = 0; i < max_size; i++) {
		Arr[i] = i;
	}
}

unittest(SetExternalStore)
{
	const int max_size = 128;
	int store[max_size];

	Array<int> Arr;
	Arr.setBackingStore(store);

	for (size_t i = 0; i < max_size; i++) {
		Arr[i] = i;
	}
}

unittest(Iteration)
{
	const int max_size = 128;
	Array<int> Arr(max_size);

	size_t ctr = 0;
	for (int &i : Arr) {
		i = ctr++;
	}

	for (int &i : Arr) {
		assertEqual(i, Arr[i]);
		assertEqual(i, Arr.at(i));
	}
}

unittest(Fill)
{
	const int max_size = 128;
	Array<int> Arr(max_size);
	Arr.fill(0);

	for (size_t i = 0; i < max_size; i++) {
		assertEqual(Arr[i], 0);
	}

	Arr.fill(INT_MIN);

	for (size_t i = 0; i < max_size; i++) {
		assertEqual(Arr[i], INT_MIN);
	}
}

unittest(Swap)
{
	const int max_size = 128;
	Array<int> Arr_A(max_size);
	Array<int> Arr_B(max_size);
	Arr_A.fill('A');
	Arr_B.fill('B');

	Arr_A.swap(Arr_B);
	assertEqual(Arr_B.back(), 'A');
	assertEqual(Arr_A.back(), 'B');
}

unittest(Getters)
{
	const int max_size = 128;
	Array<int> Arr(max_size);

	assertEqual(0, Arr.size());
	assertEqual(true, Arr.empty());
}

unittest_main()
