#include "SensorTemp.hpp"

SensorTemp::SensorTemp(const uint8_t pin, const unsigned long  sampling_interval)
    : Sensor(sampling_interval)
#ifndef ARDUINO_CI
    , _wire(pin)
    , _dallas(&_wire)
#endif
{
}

SensorTemp::~SensorTemp()
{
}

bool SensorTemp::Init()
{
#ifndef ARDUINO_CI
    _dallas.begin();
#endif
	return (true);
}

int16_t SensorTemp::GetTemp()
{
    return (_data._celsius);
}

bool SensorTemp::Update()
{
	bool error_occured = false;

    if (!_timer.Unlock())
        return (true);

#ifndef ARDUINO_CI
    _dallas.requestTemperatures();
    _data._celsius = (int)_dallas.getTempCByIndex(0);
#endif

	if (_data._monitoring_enabled) {
		if (_data._celsius < _data._lower_limit) {
			_data._errno = SensorDataTemp::TEMP_CAP_LOWER;
			error_occured = true;
		} else if (_data._celsius < _data._lower_limit) {
			_data._errno = SensorDataTemp::TEMP_CAP_UPPER;
			error_occured = true;
		}
	}

    return (error_occured == false);
}

void SensorTemp::SetMonitoringParameters(const uint16_t lower_limit, const uint16_t upper_limit)
{
	_data._lower_limit = lower_limit;
	_data._upper_limit = upper_limit;
}

/*
 * SensorDataTemp
 */

int16_t SensorDataTemp::GetTemp()
{
    return (_celsius);
}

