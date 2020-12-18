#ifndef INTERFACE_ROS_HPP
#define INTERFACE_ROS_HPP

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#include "Common/Datatypes.hpp"
#include "Interfaces/Interface.hpp"

enum e_rostopic {
    T_GPS,
    T_IMU,
	T_DRIVER,
	__T_END
};

class InterfaceROS : public Interface {
public:
    InterfaceROS(const uint16_t exec_interval);
    ~InterfaceROS();

	void HookSubscriber(auto &msg_store, void (*f)(auto &msg));
	void HookPublisher(const char *topic_name, auto &msg_store);

    void Send(const e_rostopic topic, const ros::Msg* msg);
    void Log(const e_siglevel level, const char* msg);
    bool Update();
    bool IsConnected();
private:
	ros::Publisher *_publishers[__T_END];
	//ros::Subscriber *_subscribers[__T_END];
    ros::NodeHandle _nh;
};

#endif
