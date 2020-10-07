#include "llc1.hpp"

/*
** SAMPLE CODE (for now) : do not upload without verifying libraries and ports!
*/

static unsigned long globMillis;

// example of how to use ros publish/subscribe
ros::NodeHandle node_handle;

std_msgs::String pub_msg; 
std_msgs::UInt16 sub_msg;

void subscriberCallback(const std_msgs::UInt16& sub_msg) {
  if (sub_msg.data == 1) {
	//react to event
  } else {
	//do something else
  }
}

ros::Publisher						publisher("pub_name", &pub_msg);
ros::Subscriber<std_msgs::UInt16>	subscriber("sub_name", &subscriberCallback);

int main(void)
{
	node_handle.initNode();
  	node_handle.advertise(publisher);
  	node_handle.subscribe(subscriber);

	// example loop
	while (1)
	{
		if (HIGH == HIGH) {
    		pub_msg.data = "HIGH";
  		} else {
    		pub_msg.data = "LOW";
  		}
 		publisher.publish( &pub_msg );
  		node_handle.spinOnce();
	}

    SensorGPS sg(3, 4);
	SensorHall(15, 16, 0, 16, &globMillis);
    SensorCurrent(5);
    SensorTemp(8);
}
