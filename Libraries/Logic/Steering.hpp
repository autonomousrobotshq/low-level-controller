#ifndef LOGIC_STEERING_HPP
#define LOGIC_STEERING_HPP
#include "Sandbox/Sandbox.hpp"

using namespace sb;

enum e_drivestate {
	TURNING,
	DRIVING,
	DONE
};

class LogicSteering {
public:
    LogicSteering(Sandbox &sandbox);
    ~LogicSteering();
    void driveLogic(int distance, int angle);
	void drive();

	e_drivestate state;
private:
	void _update_turn();
	void _update_distance();	
    void _pivot(int angle);
    void _turnAngle(int angle);
    void _driveDistance();
	void _stop();

private: // data members
    Sandbox& _sandbox;
	// turning var's
	int 		_starting_angle;
	int			_target_angle;

	// distance var's
	int			_target_distance;
	int			_leftcount;
	int			_rightcount;
	int			_prev_left_count;
	int			_prev_right_count;
	int			_left_diff;
	int			_right_diff;
	int			_right_power;
	int			_left_power;
	int			_target_count_distance;
	int			_numRev_distance;
	int			_offset;
	// const never changing var's
	const int 	_power = 50; // needs adjustments
    const int 	_countsPerRev = 64;
    const int 	_wheelDiam = 120;
    const float _wheelCirc = 376.99;
    const float _pivotDiam = 203.763;
    const float _pivotCirc = 640.140;
};

#endif
