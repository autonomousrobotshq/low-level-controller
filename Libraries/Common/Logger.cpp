#include "Common/Deployment.hpp"
#include "Common/Logger.hpp"
#include "Interfaces/ROS.hpp"


Logger::Logger()
{}

Logger::~Logger()
{}

#if VERBOSITY & ROS_DEBUG
static void Logger::Log(const char* msg, LOG_LEVEL level)
{
    static ROS ros_interface& ROS::GetInstance();

    ros_interface.Send(msg, level);
}

#elif VERBOSITY & PRODUCTION
void Logger::Log(const char* msg, LOG_LEVEL level)
{
    (void)msg;
    (void)level;
}


#elif VERBOSITY & SERIAL_DEBUG
void Logger::Log(const char* msg, LOG_LEVEL level)
{
    (void)msg;
    (void)level;
}

#endif // VERBOSITY
