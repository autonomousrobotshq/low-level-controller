#ifndef SENSOR_SENSORDATA_HPP
#define SENSOR_SENSORDATA_HPP

#ifdef ROS
# include "ros.h"
#endif

class Sensor;

class SensorData {
	public:
		SensorData();
		virtual ~SensorData();
	private:
		unsigned long _timestamp;
		unsigned long _interval_timestamp;
#ifdef ROS
	public:
		SensorData(const char *topic_name, ros::Msg *msg);
		virtual void Publish();
		void PublishMsg(const ros::Msg * msg);
		virtual ros::Publisher *GetPublisher();
		bool IsPublishingEnabled();
		void EnablePublishing();
		void DisablePublishing();
	private:
		ros::Publisher *_pub;
		bool _publishing_enabled = false;
#endif
};

#endif
