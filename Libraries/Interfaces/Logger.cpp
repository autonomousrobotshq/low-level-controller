#include "Interfaces/Logger.hpp"

void	InterfaceLogger::Commit(const e_loglevel loglevel, auto &msg)
{
#if (VERBOSITY & SERIAL_DEBUG)
	const static char log_msg[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
	Serial.print(log_msg[static_cast<int>(loglevel)]);
	Serial.print(": ");
	Serial.println(msg);
#else
	// pass on to ROS
#endif
}

bool	InterfaceLogger::Update()
{
	return (true);
}

InterfaceLogger::InterfaceLogger()
{

}

InterfaceLogger::~InterfaceLogger()
{

}
