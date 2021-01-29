#ifndef INTERFACE_ROS_HPP
#define INTERFACE_ROS_HPP

#include <stdint.h>
#include <ros.h>
#include "Interface.hpp"

class InterfaceROS : public Interface {
	public:
		enum e_state {
			CONNECTED,
			DISCONNECTED
		};
		enum e_loglevel {
			DEBUG,
			INFO,
			WARN,
			ERROR,
			CRIT
		};
	    InterfaceROS(const unsigned long update_interval);
	    ~InterfaceROS();
		bool Init(const unsigned long baudrate = 115200);
	    void AddPublisher(ros::Publisher& p);
	    void AddSubscriber(ros::Subscriber_& s);
	
	    void Log(const e_loglevel level, const char* msg);
	    bool Update();
	    bool IsConnected();
		bool AttemptConnect();
		e_state GetState();
	
	private:
		static ros::NodeHandle _nodehandle;
		e_state _state;
};

#endif
