#ifndef SENSOR_IMU_HPP
#define SENSOR_IMU_HPP

#include <LSM303.h>

#include "Sensor.hpp"
#include "PeakFilter.hpp"
#include "Vec3.hpp"

namespace IMU {
	typedef struct cal_s {
	    const int16_t x_min;                                                        
	    const int16_t x_max;                                                        
	    const int16_t y_min;                                                        
	    const int16_t y_max;                                                        
	    const int16_t z_min;                                                        
	    const int16_t z_max;                                                        
	} cal_t;
};

class SensorIMU : public Sensor {
public:
    SensorIMU(const uint16_t sample_count, const unsigned long sampling_interval);
    ~SensorIMU();
	bool Init(const IMU::cal_t mag_cal);
    bool Update();
    int16_t GetNavigationAngle();
    Vec3 GetMagnetometerData();
    void GetMagnetometerData(int16_t* x, int16_t* y, int16_t* z);
    Vec3 GetAccelerometerData();
    void GetAccelerometerData(int16_t* x, int16_t* y, int16_t* z);

private:
    LSM303 _compass;
    int16_t _navigation_angle;
    PeakFilter _filter;
	const uint16_t _sample_count;
};

#endif
