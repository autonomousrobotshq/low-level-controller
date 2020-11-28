#include "Sandbox/Sandbox.hpp"

namespace sandbox {

Sandbox::Sandbox()
{
	if (sb)
	{
		// crit: "Second initialisation of Sandbox!"
	}
	else
	{
		sb = this;
	}

}

Sandbox::~Sandbox()
{

}

void	Sandbox::Setup()
{

}

void	Sandbox::SpinOnce()
{

}

void	Driver(e_corner corner, e_drive_action action)
{

}

} //namespace sandbox
