#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Interfaces/ROS.hpp"
/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox sandbox;
ROS ros_test;


int main(void)
{

	sandbox.Setup();
	while (true)
	{
		// all your code here
		sandbox.SpinOnce();
		ros_test.SpinOnce();
	}
}
