#ifndef SENSOR_IMU_HPP
#define SENSOR_IMU_HPP

#include <LSM303.h>

#include "Sensor.hpp"
#include "PeakFilter.hpp"
#include "Vec3.hpp"

#ifdef ROS
# include "spine_msg/msg_imu.h"
#endif

#include <Sensor.hpp>

class SensorDataIMU : public SensorData {
	public:
		enum error {
			ACCELERATION_CAP,
			MAGNETO_CAP_LOWER,
			MAGNETO_CAP_UPPER
		};
    	int16_t GetNavigationAngle();
    	Vec3<int16_t> GetMagnetometerData();
    	void GetMagnetometerData(int16_t* x, int16_t* y, int16_t* z);
    	Vec3<int16_t> GetAccelerometerData();
    	void GetAccelerometerData(int16_t* x, int16_t* y, int16_t* z);
	private:
		friend class SensorIMU;
    	int16_t _navigation_angle;
		Vec3<int16_t> _magneto;
		Vec3<int16_t> _accelero;
		Vec3<uint16_t> _max_acceleration;
		Vec3<int16_t> _max_magneto;
		Vec3<int16_t> _min_magneto;
#ifdef ROS
	public:
		void Publish();
	private:
		spine_msg::msg_imu _msg_imu;
#endif
};

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
	bool Init(const IMU::cal_t &mag_cal);
    bool Update();
	void SetMonitoringParameters(const Vec3<uint16_t> &max_acceleration, const Vec3<int16_t> &min_magneto, const Vec3<int16_t> &max_magneto);
    int16_t GetNavigationAngle();
    Vec3<int16_t> GetMagnetometerData();
    void GetMagnetometerData(int16_t* x, int16_t* y, int16_t* z);
    Vec3<int16_t> GetAccelerometerData();
    void GetAccelerometerData(int16_t* x, int16_t* y, int16_t* z);

private:
    LSM303 _compass;
    int16_t _navigation_angle;
    PeakFilter<uint16_t> _filter;
	const uint16_t _sample_count;
	SensorDataIMU _data;
};

#endif
