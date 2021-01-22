#include "SensorUltrasonic.hpp"

// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
#define ADC_RESOLUTION (1023.0)

/*
 * SensorUltrasonic
 */

SensorUltrasonic::SensorUltrasonic(const uint8_t pin, const uint16_t max_depth, const uint16_t sample_count, const unsigned long sampling_interval)
    : Sensor(sampling_interval)
    , _analog_pin(pin)
	, _filter(sample_count)
	, _sampling_count(sample_count)
	, _data(max_depth)
{
}

SensorUltrasonic::~SensorUltrasonic() { }

bool SensorUltrasonic::Init()
{
    pinMode(_analog_pin, INPUT);
	return (true);
}

bool SensorUltrasonic::Update()
{
	bool error_occured = false;

    if (!_timer.Unlock())
		return (true);

	_filter.Reset();
	for (uint16_t i = 0; i < _sampling_count; i++)
    	_filter.NewReading(analogRead(_analog_pin));

	const uint16_t avg = _filter.GetFilteredSignal();
    _data._distance = (avg * _data._max_depth) / ADC_RESOLUTION;

	if (_data._monitoring_enabled) {
		if (_data._distance < _data._lower_limit) {
			_data._errno = SensorDataUltrasonic::DISTANCE_CAP_LOWER;
			error_occured = true;
		} else if (_data._distance < _data._lower_limit) {
			_data._errno = SensorDataUltrasonic::DISTANCE_CAP_UPPER;
			error_occured = true;
		}
	}

    return (error_occured == false);
}

SensorDataUltrasonic &SensorUltrasonic::RetreiveData()
{
	return _data;
}

void SensorUltrasonic::SetMonitoringParameters(const uint16_t lower_limit, const uint16_t upper_limit)
{
	_data._lower_limit = lower_limit;
	_data._upper_limit = upper_limit;
}

uint16_t SensorUltrasonic::GetDistance()
{
    return ((_data._distance > _data._max_depth) ? _data._max_depth : _data._distance);
}

/*
 * SensorDataUltrasonic
 */

SensorDataUltrasonic::SensorDataUltrasonic(const uint16_t max_depth)
	: _max_depth(max_depth)
{
}

uint16_t SensorDataUltrasonic::GetDistance()
{
    return ((_distance > _max_depth) ? _max_depth : _distance);
}
