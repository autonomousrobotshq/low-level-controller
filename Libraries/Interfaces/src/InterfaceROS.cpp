#include "InterfaceROS.hpp"

InterfaceROS::InterfaceROS(const unsigned long update_interval)
    : Interface(update_interval)
{
}

InterfaceROS::~InterfaceROS()
{
}

bool InterfaceROS::Init(const unsigned long baudrate)
{
	_nodehandle.getHardware()->setBaud(baudrate);
	_nodehandle.initNode();
	return (_nodehandle.spinOnce());
}

void InterfaceROS::AddSubscriber(ros::Subscriber_& s)
{
    _nodehandle.subscribe(s);
}

void InterfaceROS::AddPublisher(ros::Publisher& p)
{
    _nodehandle.advertise(p);
}

bool InterfaceROS::IsConnected()
{
    return (_nodehandle.connected());
}

bool InterfaceROS::Update()
{
    if (!IsTimeToExecute())
        return (true);

    if (!IsConnected()) {
		_state = InterfaceROS::DISCONNECTED;
		return (false);
    }
    return (_nodehandle.spinOnce() == 0);
}

bool InterfaceROS::AttemptConnect()
{
    if (!this->IsConnected()) {
        _nodehandle.spinOnce();
	}
	if (this->IsConnected()) {
		_state = InterfaceROS::CONNECTED;
		return (true);
	}
	else {
		_state = InterfaceROS::DISCONNECTED;
		return (false);
	}
}

InterfaceROS::e_state InterfaceROS::GetState()
{
	return (_state);
}

void InterfaceROS::Log(const e_loglevel level, const char* msg)
{
    switch (level) {
    case DEBUG:
        _nodehandle.logdebug(msg);
        break;
    case INFO:
        _nodehandle.loginfo(msg);
        break;
    case WARN:
        _nodehandle.logwarn(msg);
        break;
    case ERROR:
        _nodehandle.logerror(msg);
        break;
    case CRIT:
        _nodehandle.logfatal(msg);
        break;
    }
}

ros::NodeHandle InterfaceROS::_nodehandle;
