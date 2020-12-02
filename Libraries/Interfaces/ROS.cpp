#include "Interfaces/ROS.hpp"

// uint16_t distance;
// uint16_t angle;
// void driveCallBack(const std_msgs::UInt16 &msg)
// {
// 	distance = msg.data;
// 	// angle = msg.angle;
// }

ROS::ROS()
{
	  // Init ROS node
    _nh.initNode();

    std_msgs::UInt16 placeholder;
    // Init ROS topics
    _pub_GPS = new ros::Publisher("GPS", &placeholder); // TODO change to real msg
    _pub_IMU = new ros::Publisher("IMU", &placeholder); // TODO change to real msg

    std_msgs::String str_msg;
    _pub_test = new ros::Publisher("chatter", &str_msg); // TODO change to real msg
    _nh.advertise(*_pub_test);

    // Make topics available to ROS
    _nh.advertise(*_pub_GPS);
    _nh.advertise(*_pub_IMU);

    // Start receiving
    // ros::Subscriber<std_msgs::UInt16> sub("Drive", &driveCallBack );
}

ROS::~ROS()
{
    delete _pub_GPS;
    delete _pub_IMU;
}

void ROS::send(const ros::Msg *msg, ROS_TOPIC topic)
{
	switch(topic) {
      case GPS :
        _pub_GPS->publish(msg); // cast msg
        break;
      case IMU :
        _pub_IMU->publish(msg); // cast msg
         break;
      case TEST :
        _pub_test->publish(msg); // cast msg
         break;
   }
}

void ROS::SpinOnce()
{
	_nh.spinOnce();
}

void ROS::receive()
{
}