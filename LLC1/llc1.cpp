#include "llc1.hpp"

#include "pins.h"
#include "Sandbox/Sandbox.hpp"

/*
** SAMPLE CODE
*/

using namespace sandbox;

Sandbox g_sandbox;

int main(void)
{

	g_sandbox.Setup();
	while (true)
	{
		// all your code here
		g_sandbox.SpinOnce();
	}
}
