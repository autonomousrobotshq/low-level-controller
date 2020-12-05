#include "Logic/Steering.hpp"
#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include <math.h>
#define PRECISION 5
using namespace sb;

LogicSteering::LogicSteering(Sandbox& sandbox)
    : _sandbox(sandbox)
{
}

LogicSteering::~LogicSteering()
{
}

void LogicSteering::driveLogic(int distance, int angle)
{
    _starting_angle = _sandbox.GPSGetCourse();
    _target_angle = angle;
    _target_distance = distance;
    _leftcount = 0;
    _rightcount = 0;
    _prev_left_count = 0;
    _prev_right_count = 0;
    _left_diff = 0;
    _right_diff = 0;
    _right_power = 20;
    _left_power = 20;
    _left_power = 50;
    _right_power = 50; // needs to be set
    _offset = 5; // pid controller controls this
    _numRev_distance = _target_distance / _wheelCirc;
    _target_count_distance = _numRev_distance * _countsPerRev;
    if (angle != 0) {
        state = TURNING;
        _pivot(angle);
        // _turnAngle(angle);
    }
}

void LogicSteering::_pivot(int angle)
{
    if (angle < 0) {
        _sandbox.Driver(LEFT_SIDE, FORWARD, _power);
        _sandbox.Driver(RIGHT_SIDE, BACKWARD, _power);
    }
    if (angle > 0) {
        _sandbox.Driver(LEFT_SIDE, BACKWARD, _power);
        _sandbox.Driver(RIGHT_SIDE, FORWARD, _power);
    }
}

void LogicSteering::_turnAngle(int angle)
{

    if (angle > 0) {
        _sandbox.Driver(RIGHT_SIDE, HALT, _power);
        _sandbox.Driver(LEFT_SIDE, FORWARD, _power);
    } else {
        _sandbox.Driver(RIGHT_SIDE, FORWARD, _power);
        _sandbox.Driver(LEFT_SIDE, HALT, _power);
    }
}

void LogicSteering::_driveDistance()
{
    _target_count_distance = _numRev_distance * _countsPerRev;
    _sandbox.Driver(RIGHT_SIDE, FORWARD, _right_power);
    _sandbox.Driver(LEFT_SIDE, FORWARD, _left_power);
}

void LogicSteering::_stop()
{
    _sandbox.Driver(LEFT_SIDE, HALT, _power);
    _sandbox.Driver(RIGHT_SIDE, HALT, _power);
}

void LogicSteering::_update_turn()
{
    int current_angle = _sandbox.IMUGetNavigationAngle();
    if (current_angle < _target_angle + PRECISION && current_angle > _target_angle - PRECISION) {
        _stop();
        state = DRIVING;
        _driveDistance();
    }
}

void LogicSteering::_update_distance()
{

    if (abs(_rightcount) < abs(_target_count_distance) || abs(_leftcount) < abs(_target_count_distance)) {
        _left_diff = abs(_leftcount - _prev_left_count);
        _right_diff = abs(_rightcount - _prev_right_count);

        _prev_left_count = _leftcount;
        _prev_right_count = _rightcount;

        if (_left_diff > _right_diff) {
            _left_power = _left_power - _offset;
            _right_power = _right_power + _offset;
        } else if (_left_diff < _right_diff) {
            _left_power = _left_power + _offset;
            _right_power = _right_power - _offset;
        }
        _sandbox.Driver(RIGHT_SIDE, FORWARD, _right_power);
        _sandbox.Driver(LEFT_SIDE, FORWARD, _left_power);
        _leftcount += _sandbox.GetRevelation(FRONT_LEFT);
        _rightcount += _sandbox.GetRevelation(BACK_RIGHT);
    } else
        _stop();
}

void LogicSteering::drive()
{
    if (state == DONE)
        driveLogic(100, 20);
    if (state == TURNING)
        _update_turn(); // Stan komt hiervoor terug met een betere oplossing
    if (state == DRIVING)
        _update_distance();
}
