#ifndef LOGIC_STEERING_HPP
#define LOGIC_STEERING_HPP
#include "Sandbox/Sandbox.hpp"

class LogicSteering {
public:
    LogicSteering(Sandbox &sandbox);
    ~LogicSteering();
    void driveLogic(int distance, int angle);
	void update_turn();
	void update_distance();
private:
	void _VerifyDirection();
    void _turn(int angle);
    void _pivot(int angle, int rpmcount);
    void _turnAngle(int angle);
    void _driveDistance(int distance);
	void _stopturning();
	void _start_turning(int angle);

private: // data members
    Sandbox& _sandbox;
	int			_retryCount;
	int			_revelation_count;
	long		_leftcount;
	long		_rightcount;
	int 		_starting_angle;
	int			_target_count;
	int			_target_angle;
	const int 	_power = 10;
    const int 	_countsPerRev = 64;
    const int 	_wheelDiam = 120;
    const float _wheelCirc = 376.99;
    const float _pivotDiam = 203.763;
    const float _pivotCirc = 640.140;
};

#endif
