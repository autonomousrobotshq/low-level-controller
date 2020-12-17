#include "Common/Datatypes.hpp"
#include "Interfaces/Logger.hpp"
#include "Logic/Driving.hpp"

namespace DR {

using namespace sb;

bool LogicDriving::HeadTo(const uint16_t desired_heading, const uint8_t desired_throttle)
{
	_actions.clear();

	_desired_heading = desired_heading;
	_desired_throttle = desired_throttle;

	uint16_t current_heading = IMUGetNavigationAngle();
	uint8_t current_speed = DriverGetThrottle();

	if (current_speed > DRAG_SPEED_THRESHOLD
		&& (abs(current_heading - desired_heading) < DRAG_ANGULAR_THRESHOLD
		|| abs((current_heading + 360) - desired_heading) < DRAG_ANGULAR_THRESHOLD
		|| abs(current_heading - (desired_heading + 360)) < DRAG_ANGULAR_THRESHOLD))
	{
		// let's drag
	}
	else if (current_speed > 0)
	{
		// halt and adjust
		_actions.push_back(e_action::ADJUST);
		_actions.push_back(e_action::SLOWHALT);
	}
	else
	{
		// turn and drive
		if (desired_throttle > 0)
			_actions.push_back(e_action::FORWARD);
		else
			_actions.push_back(e_action::HALT);

		e_side direction = GetSpinDirection(current_heading, desired_heading);
		if (direction == LEFT)
			_actions.push_back(e_action::SPINLEFT);
		else if (direction == RIGHT)
			_actions.push_back(e_action::SPINRIGHT);
	}

	return (true);
}

void LogicDriving::MeasureSpin()
{
	uint16_t current_heading = IMUGetNavigationAngle();
	
	// check if angle is approaching target angle
	// slow down until you reach it

	if (abs(current_heading - _desired_heading) < ANGULAR_TARGET_RANGE
		|| abs((current_heading + 360) - _desired_heading) < ANGULAR_TARGET_RANGE
		|| abs(current_heading - (_desired_heading + 360)) < ANGULAR_TARGET_RANGE)
	{
		_sandbox->Driver(ALL_SIDES, HALT);
	}
	else if (abs(current_heading - _desired_heading) < SPIN_SLOWDOWN_THRESHOLD
		|| abs((current_heading + 360) - _desired_heading) < SPIN_SLOWDOWN_THRESHOLD
		|| abs(current_heading - (_desired_heading + 360)) < SPIN_SLOWDOWN_THRESHOLD)
	{
		// start slowing down
	}
}

void LogicDriving::MeasureDrag()
{
	uint16_t current_heading = IMUGetNavigationAngle();
	
	// check if angle is approaching target angle
	// slow down untill you reach it

	if (abs(current_heading - _desired_heading) < DRAG_SPEEDUP_THRESHOLD
		|| abs((current_heading + 360) - _desired_heading) < DRAG_SPEEDUP_THRESHOLD
		|| abs(current_heading - (_desired_heading + 360)) < DRAG_SPEEDUP_THRESHOLD)
	{
		// start speeding up
	}
}

int16_t LogicDriving::GetThrottleForDragSteering(const e_action action, const e_side side)
{
	(void)action;
	(void)side;
	return (0);
}

void LogicDriving::Perform(const e_action action)
{
	switch (action)
	{
		case e_action::FORWARD:
			_sandbox->Driver(ALL_SIDES, FORWARD, _desired_throttle);
		break;
		case e_action::BACKWARD:
			_sandbox->Driver(ALL_SIDES, BACKWARD, _desired_throttle);
		break;
		case e_action::HALT:
			_sandbox->Driver(ALL_SIDES, HALT);
		break;
		case e_action::SLOWHALT:
			//Driver(ALL_SIDES, SLOWHALT); -> NOT IMPLEMENTED
		break;
		case e_action::SPINLEFT:
			_sandbox->Driver(LEFT, BACKWARD, _desired_throttle);
			_sandbox->Driver(RIGHT, FORWARD, _desired_throttle);
		break;
		case e_action::SPINRIGHT:
			_sandbox->Driver(LEFT, FORWARD, _desired_throttle);
			_sandbox->Driver(RIGHT, BACKWARD, _desired_throttle);
		break;
		case e_action::DRAGLEFT:
			_sandbox->Driver(LEFT, FORWARD, GetThrottleForDragSteering(action, LEFT));
			_sandbox->Driver(RIGHT, FORWARD, GetThrottleForDragSteering(action, RIGHT));
		break;
		case e_action::DRAGRIGHT:
			_sandbox->Driver(LEFT, FORWARD, GetThrottleForDragSteering(action, LEFT)); // FORWARD ? BACKWARD
			_sandbox->Driver(RIGHT, FORWARD, GetThrottleForDragSteering(action, RIGHT)); // FORWARD ? BACKWARD
		break;
		case e_action::ADJUST:
			HeadTo(_desired_heading, _desired_throttle);
		case e_action::MEASURESPIN:
			MeasureSpin();
		case e_action::MEASUREDRAG:
			MeasureDrag();
		break;
	}
}

bool LogicDriving::Update()
{
	if (_actions.size() > 0 && _sandbox->DriverIsReady())
	{
		e_action action = _actions.back();
		_actions.pop_back();
		Perform(action);
	}
	return (true);
}

LogicDriving::LogicDriving(sb::Sandbox *sandbox)
	: _sandbox(sandbox)
	, _actions(_actions_buf, ACTION_QUEUE_LEN)
	, _desired_heading(0)
	, _desired_throttle(0)
{
	
}

LogicDriving::~LogicDriving()
{

}

} // namespace DR
