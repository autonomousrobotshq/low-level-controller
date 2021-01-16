#include "ros.h"
#include "Interfaces/ROS.hpp"
#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Common/State.hpp"
#include <Arduino.h>

static ros::NodeHandle* g_nodehandle;

// needed for Ros libraries which follow std11
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
    if (!g_nodehandle) {
        g_nodehandle = new ros::NodeHandle;
		g_nodehandle->getHardware()->setBaud(ROS_BAUDRATE);
        g_nodehandle->initNode();
    }
}

InterfaceROS::~InterfaceROS()
{
}

void InterfaceROS::AddSubscriber(ros::Subscriber_& s)
{
    g_nodehandle->subscribe(s);
}

void InterfaceROS::AddPublisher(ros::Publisher& p)
{
    g_nodehandle->advertise(p);
}

bool InterfaceROS::IsConnected()
{
    return (g_nodehandle->connected());
}

bool InterfaceROS::Update()
{
    if (!IsTimeToExecute())
        return (true);

    if (!this->IsConnected()) {
        g_nodehandle->spinOnce();
        if (!this->IsConnected()) {
            g_state = S_ROS_DISCONNECTED;
            return (false);
        }
    }
    return (g_nodehandle->spinOnce() == 0);
}

void InterfaceROS::Log(const e_siglevel level, const char* msg)
{
    switch (level) {
    case e_siglevel::DEBUG:
        g_nodehandle->logdebug(msg);
        break;
    case e_siglevel::INFO:
        g_nodehandle->loginfo(msg);
        break;
    case e_siglevel::WARN:
        g_nodehandle->logwarn(msg);
        break;
    case e_siglevel::ERROR:
        g_nodehandle->logerror(msg);
        break;
    case e_siglevel::CRIT:
        g_nodehandle->logfatal(msg);
        break;
    }
}
