#include "Arduino.h"
#include "SensorData.hpp"

#ifndef ROS 

SensorData::SensorData()
{
}

SensorData::~SensorData()
{
}

#else

SensorData::SensorData()
{
}

SensorData::~SensorData()
{
	delete _pub;
}
SensorData::SensorData(const char *topic_name, ros::Msg *msg)
	: _pub(new ros::Publisher(topic_name, msg))
{
}

void	SensorData::Publish()
{
}

void	SensorData::PublishMsg(const ros::Msg * msg)
{
	_pub->publish(msg);
}

ros::Publisher *SensorData::GetPublisher()
{
	return (_pub);
}

void SensorData::SetPublisher(const char *topic_name, ros::Msg *msg)
{
	_pub = new ros::Publisher(topic_name, msg);
}

void	SensorData::EnablePublishing()
{
	_publishing_enabled = true;
}

void	SensorData::DisablePublishing()
{
	_publishing_enabled = true;
}

bool	SensorData::IsPublishingEnabled()
{
	return (_publishing_enabled);
}

#endif

void	SensorData::UpdateTimestamps()
{
	_time_since_last_execution = millis() - _timestamp;
	_timestamp = millis();
}

unsigned long SensorData::GetTimestamp()
{
	return _timestamp;
}

unsigned long SensorData::GetTimeSinceLastExecution()
{
	return _time_since_last_execution;
}

uint8_t SensorData::GetError()
{
	return _errno;
}
