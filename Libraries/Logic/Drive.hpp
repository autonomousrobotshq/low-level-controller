#ifndef LOGIC_DRIVE_HPP
# define LOGIC_DRIVE_HPP

#include "Sandbox/Sandbox.hpp"
#include "Logic/Logic.hpp"
#include "External/Vector-1.2.0/src/Vector.h"

namespace DR {

#define ACTION_QUEUE_LEN 255

#define DRAG_SPEED_THRESHOLD 50
#define DRAG_ANGULAR_THRESHOLD 30

#define SPIN_SLOWDOWN_THRESHOLD 30
#define DRAG_SPEEDUP_THRESHOLD 15

#define ANGULAR_TARGET_RANGE 5

enum class e_action 
{
	FORWARD = 'F',
	BACKWARD = 'B',
	HALT = 'H',
	SLOWHALT = 'h',
	SPINLEFT = 'L',
	SPINRIGHT = 'R',
	DRAGLEFT = 'l',
	DRAGRIGHT = 'r',
	ADJUST = 'A',
	MEASURESPIN = 'M',
	MEASUREDRAG = 'm'
};

class LogicDriving : public Logic
{
	public:
			LogicDriving(sb::Sandbox *sandbox);
			~LogicDriving();
		bool HeadTo(const uint16_t heading, const uint8_t throttle);
		bool Update();
	private:
		void Perform(const e_action action);
		void MeasureSpin();
		void MeasureDrag();
		int16_t GetThrottleForDragSteering(const e_action action, const e_side side);
	private:
		sb::Sandbox *_sandbox;
		Vector<e_action> _actions;
		e_action _actions_buf[ACTION_QUEUE_LEN];
		uint8_t _action_index;
		uint16_t _desired_heading;
		uint16_t _desired_throttle;
};

} // namespace DR
#endif
