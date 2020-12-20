#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"

#include "Interfaces/ROS.hpp"
#include "keyboard/Key.h"
#include <ros.h>


using namespace sb;

Sandbox *sandbox;

#define _SPEED 50

void keydown_callback(const keyboard::Key &key_msg)
{
	switch (key_msg.code)
	{
		case (keyboard::Key::KEY_w):
			Driver(ALL_SIDES, FORWARD, _SPEED);
			SIGBeep(e_siglevel::INFO, 1);
		break;
		case (keyboard::Key::KEY_s):
			Driver(ALL_SIDES, BACKWARD, _SPEED);
			SIGBeep(e_siglevel::INFO, 1);
		break;
		case (keyboard::Key::KEY_a):
			Driver(LEFT, BACKWARD, _SPEED);
			Driver(RIGHT, FORWARD, _SPEED);
			SIGBeep(e_siglevel::INFO, 1);
		break;
		case (keyboard::Key::KEY_d):
			Driver(LEFT, FORWARD, _SPEED);
			Driver(RIGHT, BACKWARD, _SPEED);
			SIGBeep(e_siglevel::INFO, 1);
		break;
		case (keyboard::Key::KEY_b):
			Driver(ALL_SIDES, HALT);
			SIGBeep(e_siglevel::INFO, 1);
		break;
		case (keyboard::Key::KEY_SPACE):
			Driver(ALL_SIDES, SLOWHALT);
			SIGBeep(e_siglevel::INFO, 1);
		break;
	}
}

void keyup_callback(const keyboard::Key &key_msg)
{
	Driver(ALL_SIDES, SLOWHALT);
	(void)key_msg;
}

ros::Subscriber<keyboard::Key>  keydown_sub("/keyboard/keydown", &keydown_callback);
ros::Subscriber<keyboard::Key>  keyup_sub("/keyboard/keyup", &keyup_callback);

bool LogicDriverUpdate(void) // is called just before update of motorcontroller in Sandbox::Spinonce
{
	return (true);
}

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();
	sandbox->SetLogicDriverUpdate(LogicDriverUpdate);
	sandbox->ROSAddSubscriber(keydown_sub);
	sandbox->ROSAddSubscriber(keyup_sub);
}

void loop() // loops indefinitely
{
	// all your code here
	sandbox->SpinOnce();

	delay(20);
}

void post() // runs when loop() breaks
{
	sandbox->Shutdown();
}
