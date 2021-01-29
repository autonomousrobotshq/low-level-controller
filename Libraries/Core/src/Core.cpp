#include "Core.hpp"

Core::Core()
	: _controllers(_controller_store)
	, _interfaces(_interface_store)
{
}

Core::~Core()
{
}

bool Core::Update()
{
	bool error = false;
	for (Controller *c : _controllers) {
		if (! c->Update()) {
			error = true;
		}
	}
	for (Interface *i : _interfaces) {
		if (! i->Update()) {
			error = true;
		}
	}
	return (errors == 0);
}

bool Core::AddController(Controller *c)
{
	if (_controllers.size() < _max_controllers) {
		_controllers.push_back(c);
		return true;
	} else {
		return false;
	}
}

bool Core::AddInterface(Interface *i)
{
	if (_interfaces.size() < _max_interfaces) {
		_interfaces.push_back(c);
	} else {
		return false;
	}
}

Core Spine = Core();
