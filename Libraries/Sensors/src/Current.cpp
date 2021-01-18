#include <Arduino.h>
#include "Current.hpp"

// should probably check which board this is                                    
#define ADC_RESOLUTION (1023.0)

SensorCurrent::SensorCurrent(const uint8_t analogPin, const uint8_t sample_count, const unsigned long sampling_interval)
    : Sensor(sampling_interval)
    , _analogPin(analogPin)
	, _filter(sample_count)
	, _sample_count(sample_count)
{
}

SensorCurrent::~SensorCurrent()
{
}

bool SensorCurrent::Init()
{
    _vref = ReadReferenceVoltage();
	return (true);
}

bool SensorCurrent::Update()
{
    if (!IsTimeToExecute())
        return (true);
    _current = ReadDCCurrent();
    return (true);
}

uint16_t SensorCurrent::GetCurrentMilliAmps()
{
    return (_current);
}

uint8_t SensorCurrent::GetCurrentAmps()
{
    return (_current / 1000);
}

/*read DC Current Value
 * https://github.com/nxcosa/20A-CURRENT-SENSOR/blob/master/_20AcurrentSensor.ino
 */
uint16_t SensorCurrent::ReadDCCurrent()
{
	_filter.Reset();
    for (int i = 0; i < _sample_count; i++) {
        _filter.NewReading(analogRead(_analogPin));
    }
    const uint16_t median_reading = _filter.GetFilteredSignal();
	int16_t dc_current = (median_reading / ADC_RESOLUTION * _vref - _vref / 2.0) / _mVperAmp; //Sensitivity:100mV/A, 0A @ Vcc/2
    return ((dc_current < 0) ? 0 : dc_current);
}

/* read reference voltage
 * https://github.com/nxcosa/20A-CURRENT-SENSOR/blob/master/_20AcurrentSensor.ino
 * If testing with Arduino-CI, don't attempt to use hardware defines (breaks arduino-ci's compilation of targets) 
 */
#ifndef ARDUINO_CI
long SensorCurrent::ReadReferenceVoltage()
{
    long result;
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_AT90USB1286__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    ADCSRB &= ~_BV(MUX5); // Without this the function always returns -1 on the ATmega2560 http://openenergymonitor.org/emon/node/2253#comment-11432
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#endif
#if defined(__AVR__)
    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC))
        ;
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result; //1100mV*1024 ADC steps http://openenergymonitor.org/emon/node/1186
    return result;
#elif defined(__arm__)
    return (3300); //Arduino Due
#else
    return (3300); //Guess that other un-supported architectures will be running a 3.3V!
#endif
}
#else
long SensorCurrent::ReadReferenceVoltage()
{
	return (4500); // assume 4.5V for testing
}
#endif
