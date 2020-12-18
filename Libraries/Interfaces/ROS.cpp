#include <Arduino.h>
#include "Common/Datatypes.hpp"
#include "Common/State.hpp"
#include "Interfaces/ROS.hpp"

// needed for Ros libraries which follow std11 (not std14)
void operator delete(void* ptr, size_t size)
{
    free(ptr);
    (void)size;
}

void operator delete[](void* ptr, size_t size)
{
    free(ptr);
    (void)size;
}

InterfaceROS::InterfaceROS(const uint16_t exec_interval)
    : Interface(exec_interval)
{
    // Init ROS node
    _nh.initNode();
}

InterfaceROS::~InterfaceROS()
{
}

void InterfaceROS::HookSubscriber(auto &msg_store, void (*f)(auto &msg))
{
	(void)msg_store;
	(void)f;
}

void InterfaceROS::HookPublisher(const char *topic_name, auto &msg_store)
{
	(void)topic_name;
	(void)msg_store;
}

void InterfaceROS::Send(const e_rostopic topic, const ros::Msg* msg)
{
	(void)topic;
	(void)msg;
}

bool InterfaceROS::IsConnected()
{
    return (_nh.connected());
}

bool InterfaceROS::Update()
{
	if (!IsTimeToExecute())
		return (true);

	if (!this->IsConnected())
	{
		g_state = S_ROS_DISCONNECTED;
		return (false);
	}

    return (_nh.spinOnce() == 0);
}

void InterfaceROS::Log(const e_siglevel level, const char* msg)
{
    switch (level) {
    case e_siglevel::DEBUG:
        _nh.logdebug(msg);
        break;
    case e_siglevel::INFO:
        _nh.loginfo(msg);
        break;
    case e_siglevel::WARN:
        _nh.logwarn(msg);
        break;
    case e_siglevel::ERROR:
        _nh.logerror(msg);
        break;
	case e_siglevel::CRIT:
        _nh.logfatal(msg);
        break;
    }
}
