#ifndef INTERFACE_ROS_HPP
#define INTERFACE_ROS_HPP

#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <ros.h>
#include "Interfaces/Interface.hpp"

enum ROS_TOPIC {
    GPS,
    IMU,
    TEST
};

enum ROS_LOG_LEVEL {
    ROS_DEBUG,
    ROS_INFO,
    ROS_WARN,
    ROS_ERROR,
    ROS_FATAL
};

///*
//    Singleton class for everything InterfaceROS related
//*/
class InterfaceROS : public Interface {
public:
    //static InterfaceROS& GetInstance();

    //InterfaceROS(InterfaceROS const&) = delete; // Don't Implement
    //void operator=(InterfaceROS const&) = delete; // Don't implement

    //InterfaceROS();
    //~InterfaceROS();
    InterfaceROS(const uint16_t exec_interval);
    ~InterfaceROS();

    void Send(const ros::Msg* msg, ROS_TOPIC topic);
    void Log(const char* msg, ROS_LOG_LEVEL level);
    void SpinOnce();
    bool Connected();

private:
    ros::NodeHandle _nh;
    ros::Publisher* _pub_GPS;
    ros::Publisher* _pub_IMU;
    std_msgs::UInt16 _uint16_msg;

    // Testing purposes only
    ros::Publisher* _pub_test;
    std_msgs::String _str_msg;
};

#endif
