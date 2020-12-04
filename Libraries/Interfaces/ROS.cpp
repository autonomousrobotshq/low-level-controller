#include "Interfaces/ROS.hpp"

ROS& ROS::GetInstance()
{
    static ROS instance;

    return instance;
}

ROS::ROS()
{
    // Init ROS node
    _nh.initNode();

    // Init ROS topics
    _pub_test = new ros::Publisher("chatter", &_str_msg); // Left this in for testing purposes
    _nh.advertise(*_pub_test);

    // Init ROS topics GPS and IMU
    _pub_GPS = new ros::Publisher("GPS", &_uint16_msg); // TODO change to custom msg type
    _nh.advertise(*_pub_GPS);
    _pub_IMU = new ros::Publisher("IMU", &_uint16_msg); // TODO change to custom msg type
    _nh.advertise(*_pub_IMU);
}

ROS::~ROS()
{
    delete _pub_GPS;
    delete _pub_IMU;
}

void ROS::Send(const ros::Msg* msg, ROS_TOPIC topic)
{
    switch (topic) {
    case GPS:
        _pub_GPS->publish(msg); // cast msg
        break;
    case IMU:
        _pub_IMU->publish(msg); // cast msg
        break;
    case TEST:
        _pub_test->publish(msg); // cast msg
        break;
    }
}

bool ROS::Connected()
{
    return _nh.connected();
}

void ROS::SpinOnce()
{
    _nh.spinOnce();
}

void ROS::Log(const char* msg, ROS_LOG_LEVEL level)
{
    switch (level) {
    case ROS_DEBUG:
        _nh.logdebug(msg);
        break;
    case ROS_INFO:
        _nh.loginfo(msg);
        break;
    case ROS_WARN:
        _nh.logwarn(msg);
        break;
    case ROS_ERROR:
        _nh.logerror(msg);
        break;
    case ROS_FATAL:
        _nh.logfatal(msg);
        break;
    }
}
