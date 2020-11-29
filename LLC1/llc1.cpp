#include "deployment.h"
#include "pins.h"

#include "Sandbox/Sandbox.hpp"

/*
** SAMPLE CODE
*/

Sandbox sandbox;

int main(void)
{

	sandbox.Setup();
	while (true)
	{
		// all your code here
		sandbox.SpinOnce();
	}
}
