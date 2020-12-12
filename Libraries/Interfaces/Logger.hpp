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
		InterfaceLogger();
		~InterfaceLogger();
		void Commit(const e_loglevel loglevel, auto &msg);
		bool Update();
	private:
};

#endif
