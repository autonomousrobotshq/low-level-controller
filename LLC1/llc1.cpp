#include "llc1.hpp"
#include "driveLogic.hpp"
#include "robotEntity.hpp"
/*
** SAMPLE CODE (for now) : do not upload without verifying libraries and ports!
*/

// this is the global time variable which every class instance may use to
// perform time based logic.
static unsigned long globMillis;

// example of how to use ros publish/subscribe
ros::NodeHandle node_handle;

std_msgs::String pub_msg; 
std_msgs::UInt16 sub_msg;

// here we should create the robot robotEntity with pin lay-out and everything

void subscriberCallback(const std_msgs::UInt16& sub_msg) {
  if (sub_msg.data == 1) 
  {
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

	robotEntity *robot = new robotEntity();
	// everything down here is what is being received from the ros nodes
	int				targetDirection = 90; // degree's from camera view of target position
	float 			targetDistance = 1000.0; // distance towards the new target position in cm
	// coordinates	coordinates;
	// coordinates.y = 10.0; // coordinates which are being received from ros
	// coordinates.x = 5.0; // coordinates which are being received from ros
	driveLogic drive(coordinates, targetDirection, targetDistance, robot);
	drive.Drive();
}
