#include "llc1.hpp"

/*
** SAMPLE CODE
*/

use namespace sandbox;

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
