#include <Wire.h>
#include <LSM303.h>
#include "Controllers/Motor.hpp"
#include "Controllers/Lifetime.hpp"
#include "Common/Platform.hpp"

LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};
//LSM303::vector<int16_t> running_min = {-614, -524, -528}, running_max = {358, 522, 515};

char report[80];

ControllerMotor *g_mot;
ControllerLifetime *g_lifetime;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!compass.init(LSM303::device_DLH, LSM303::sa0_auto))
  {
		Serial.println("FAILED TO INITIALIZE IMU");
		exit(1);
  }
  compass.enableDefault();
   Wire.beginTransmission(0x3C >> 1);
  Wire.write(0x01);
  //HEX = BIN              RANGE  GAIN X/Y/Z   GAIN Z
  //0x20 = 0b00100000   ±1.3     1055             950 (default)
  //0x40 = 0b01000000   ±1.9     795               710
  //0x60 = 0b01100000   ±2.5     635               570
  //0x80 = 0b10000000   ±4.0     430               385
  //0xE0 = 0b11100000   ±8.1     230               205
  Wire.write(0x80);
  Wire.endTransmission();

  g_mot = new ControllerMotor();
  g_lifetime = new ControllerLifetime(LLC::pins_relay);
  g_lifetime->Lifephase(STARTUP);
}

void loop() {  
  compass.read();
  
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
  
  snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}    max: {%+6d, %+6d, %+6d}, heading: %+6d",
    running_min.x, running_min.y, running_min.z,
    running_max.x, running_max.y, running_max.z, (int)compass.heading());
  Serial.println(report);
  
  delay(100);
  g_mot->Driver(LEFT_SIDE, FORWARD, 50);
  g_mot->Driver(RIGHT_SIDE, BACKWARD, 50);
  g_mot->Update();
}
