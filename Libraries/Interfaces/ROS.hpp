#ifndef INTERFACE_ROS_HPP
#define INTERFACE_ROS_HPP

#include <stdint.h>

#include <ros.h>
#include "ros/subscriber.h"
#include "ros/publisher.h"

#include "Common/Datatypes.hpp"
#include "Interfaces/Interface.hpp"

class InterfaceROS : public Interface {
public:
    InterfaceROS(const uint16_t exec_interval);
    ~InterfaceROS();

	void AddPublisher(ros::Publisher &p);
	void AddSubscriber(ros::Subscriber_ &s);

    void Log(const e_siglevel level, const char* msg);
    bool Update();
    bool IsConnected();
private:
};

#endif
