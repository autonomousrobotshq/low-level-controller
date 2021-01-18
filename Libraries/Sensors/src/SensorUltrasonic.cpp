#include "SensorUltrasonic.hpp"

// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
#define ADC_RESOLUTION (1023.0)

SensorUltrasonic::SensorUltrasonic(const uint8_t pin, const uint16_t max_depth, const uint16_t sample_count, const unsigned long sampling_interval)
    : Sensor(sampling_interval)
    , _analog_pin(pin)
	, _max_depth(max_depth)
	, _filter(sample_count)
	, _sampling_count(sample_count)
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
    if (!IsTimeToExecute())
		return (true);

	_filter.Reset();
	for (uint16_t i = 0; i < _sampling_count; i++)
    	_filter.NewReading(analogRead(_analog_pin));

	const uint16_t avg = _filter.GetFilteredSignal();
    _distance = (avg * _max_depth) / ADC_RESOLUTION;

    /*
	**	No error handling implemented yet (if at all necessary).
	*** RE: definitely necessary: take average and store last average value
	*** to filter out wrong readings.
	*/

    return (true);
}

uint16_t SensorUltrasonic::GetDistance()
{
    return ((_distance > _max_depth) ? _max_depth : _distance);
}
