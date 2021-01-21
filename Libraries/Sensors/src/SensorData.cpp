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
	: _pub(NULL)
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
