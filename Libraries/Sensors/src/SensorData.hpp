#ifndef SENSOR_SENSORDATA_HPP
#define SENSOR_SENSORDATA_HPP

#ifdef ROS
# include "ros.h"
#endif

class SensorData {
	public:
		SensorData();
		virtual ~SensorData();
		unsigned long GetTimestamp();
		unsigned long GetTimeSinceLastExecution();
		uint8_t GetError();
		void EnableMonitoring();
		void DisableMonitoring();
	protected:
		void UpdateTimestamps();
		uint8_t _errno = 0;
		bool _monitoring_enabled = false;
	private:
		unsigned long _timestamp = 0;
		unsigned long _time_since_last_execution = 0;
#ifdef ROS
	public:
		SensorData(const char *topic_name, ros::Msg *msg);
		virtual void Publish();
		void PublishMsg(const ros::Msg * msg);
		virtual ros::Publisher *GetPublisher();
		void SetPublisher(const char *topic_name, ros::Msg *msg);
		bool IsPublishingEnabled();
		void EnablePublishing();
		void DisablePublishing();
	private:
		ros::Publisher *_pub = NULL;
		bool _publishing_enabled = false;
#endif
};

#endif
