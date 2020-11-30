#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"

/*
** SAMPLE CODE
*/

using namespace sb;

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
