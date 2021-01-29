#ifndef CORE_HPP
#define CORE_HPP

#include "Controller.hpp"
#include "Interface.hpp"

class Core
{
	public:
		Core();
		~Core();
		bool Update();
		bool AddController(Controller *c);
		bool AddInterface(Interface *i);
	private:
		static const uint8_t _max_controllers = 12;
		Controller *_controller_store[_max_controllers];
		Vector<Controller*> _controllers;

		static const uint8_t _max_interfaces = 12;
		Interface *_interface_store[_max_interfaces];
		Vector<Interface*> _interfaces;

};

extern Core Spine;

#endif
