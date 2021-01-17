#include "Controllers_Awareness.hpp"

ControllerAwareness::ControllerAwareness(InterfaceROS* interface_ros)
    : _sensor_gps(LLC::pins_gps, LLC::exec_intervals.gps)
    , _sensor_imu(LLC::pins_imu, LLC::imu_calibration_accelerometer, LLC::imu_calibration_magnetometer, LLC::exec_intervals.imu)
    , _interface_ros(interface_ros)
    , _pub_gps(LLC::str_rostopics[LLC::GPS], &_msg_gps)
    , _pub_imu(LLC::str_rostopics[LLC::IMU], &_msg_imu)
{
    _interface_ros->AddPublisher(_pub_gps);
    _interface_ros->AddPublisher(_pub_imu);
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        _ultrasonic_sensors[i] = new SensorUltrasonic(LLC::pins_ultrasonic[i], LLC::exec_intervals.ultrasonic);
    for (int i = 0; i < NUM_TEMP; i++)
        _temperature_sensors[i] = new SensorTemp(LLC::pins_temp[i], LLC::exec_intervals.temperature);
    for (int i = 0; i < NUM_MOTORS; i++)
        _current_sensors[i] = new SensorCurrent(LLC::pins_current[i], LLC::exec_intervals.current);
}

ControllerAwareness::~ControllerAwareness()
{
    for (int i = 0; i < NUM_ULTRASONIC; i++)
        delete (_ultrasonic_sensors[i]);
    for (int i = 0; i < NUM_TEMP; i++)
        delete (_temperature_sensors[i]);
    for (int i = 0; i < NUM_MOTORS; i++)
        delete (_current_sensors[i]);
}

uint8_t ControllerAwareness::GetDistance(const e_corner corner)
{
    return (_ultrasonic_sensors[corner]->GetDistance());
}

uint8_t ControllerAwareness::GetTemperature(const uint8_t temp_sensor)
{
    return (_temperature_sensors[temp_sensor]->GetTemp());
}

uint8_t ControllerAwareness::GetCurrent(const e_corner corner)
{
    return (_current_sensors[corner]->GetCurrent());
}

void ControllerAwareness::PublishData()
{
    _sensor_gps.GetLocation(&_msg_gps.lat, &_msg_gps.lon);

    _sensor_imu.GetAccelerometerData(&_msg_imu.accel_x, &_msg_imu.accel_y, &_msg_imu.accel_z);
    _sensor_imu.GetMagnetometerData(&_msg_imu.mag_x, &_msg_imu.mag_y, &_msg_imu.mag_z);
    _msg_imu.angle = _sensor_imu.GetNavigationAngle();

    _pub_gps.publish(&_msg_gps);
    _pub_imu.publish(&_msg_imu);
}

bool ControllerAwareness::Update()
{
	// these functions need to be parametrized
    for (int i = 0; i < NUM_MOTORS; i++) {
        if (_current_sensors[i]->Update()) {
            if (_current_sensors[i]->GetCurrent() > CRITICAL_CURRENT) {
                g_state = S_CURRENT_CRIT;
                return (false);
            }
        } else {
            g_state = S_CURRENT_ERROR;
            return (false);
        }
    }

    for (int i = 0; i < NUM_ULTRASONIC; i++) {
        if (_ultrasonic_sensors[i]->Update()) {
            if (_ultrasonic_sensors[i]->GetDistance() < CRITICAL_DISTANCE) {
                g_state = S_PROXIMITY_CRIT;
                return (false);
            } else if (_ultrasonic_sensors[i]->GetDistance() < DANGEROUS_DISTANCE) {
                g_state = S_PROXIMITY_WARN;
                return (false);
            }
        } else {
            g_state = S_PROXIMITY_ERROR;
            return (false);
        }
    }

    for (int i = 0; i < NUM_TEMP; i++) {
        if (_temperature_sensors[i]->Update()) {
            if (_temperature_sensors[i]->GetTemp() > CRITICAL_TEMPERATURE) {
                g_state = S_TEMP_CRIT;
                return (false);
            } else if (_temperature_sensors[i]->GetTemp() > DANGEROUS_TEMPERATURE) {
                g_state = S_TEMP_WARN;
                return (false);
            }
        } else {
            g_state = S_TEMP_ERROR;
            return (false);
        }
    }

	// FLOATING POINT EXCEPTION: somewhere in gps / imu !
    //if (!_sensor_gps.Update()) {
    //    g_state = S_GPS_ERROR;
    //    return (false);
    //}

    //if (!_sensor_imu.Update()) {
    //    g_state = S_IMU_ERROR;
    //    return (false);
    //}

    //PublishData();
    return (true);
}
