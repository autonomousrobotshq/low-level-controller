#ifndef INTERFACE_ROS_HPP
#define INTERFACE_ROS_HPP

#include "Interfaces/Interface.hpp"
#include "ros.h"
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

enum ROS_TOPIC
{
    GPS,
    IMU
};

class ROS : public Interface {
public:
    ROS();
    ~ROS();

    void send(const ros::Msg *msg, ROS_TOPIC topic);
    void receive();
    void SpinOnce();

private:
    ros::NodeHandle _nh;
    ros::Publisher *_pub_GPS;
    ros::Publisher *_pub_IMU;
};

#endif
