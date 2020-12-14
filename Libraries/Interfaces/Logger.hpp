#ifndef INTERFACES_LOGGER_HPP
#define INTERFACES_LOGGER_HPP

#include "Interfaces/Interface.hpp"
#include "Interfaces/ROS.hpp"

enum class e_loglevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

enum class e_topic {
    GPS,
    IMU
};

class InterfaceLogger : public Interface
{
	public:
		InterfaceLogger(const uint16_t exec_interval_ros);
		~InterfaceLogger();
		void Commit(const e_loglevel loglevel, auto &msg);
		bool Update();
	private:
		InterfaceROS _interface_ros;
};

#endif
