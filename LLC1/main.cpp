#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Interfaces/ROS.hpp"
// /*
// ** SAMPLE CODE
// */

using namespace sb;

// Sandbox sandbox;
ROS ros_test;
std_msgs::String str_msg;
char hello[13] = "hello world!";

// #include <ros.h>
// #include <std_msgs/String.h>
  
// ros::NodeHandle nh;

// ros::Publisher chatter("chatter", &str_msg);

// char hello[13] = "hello world!";

// void setup()
// {
// 	nh.initNode();
// 	nh.advertise(chatter);
// }

// void loop(void)
// {
// 	str_msg.data = hello;
// 	chatter.publish( &str_msg );
// 	nh.spinOnce();
// 	delay(5000);

void setup() //runs on startup
{

	// sandbox.Setup();
}

void loop() // loops indefinitely
{
	str_msg.data = hello;
	ros_test.send(&str_msg, TEST);
	ros_test.SpinOnce();
	delay(5000);
	// all your code here
	// sandbox.SpinOnce();
}
