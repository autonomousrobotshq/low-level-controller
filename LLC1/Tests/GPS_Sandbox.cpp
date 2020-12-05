#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Sensors/GPS.hpp"

#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("Online");
    Serial.println();

    SensorGPS gps(LLC::pins_gps);

    while (true) {
        if (!gps.Update())
            Serial.println("Update failed!");

        float flat, flon;
        gps.GetLocation(&flat, &flon);
        Serial.print("FLAT: ");
        Serial.print(flat);
        Serial.print(" FLON: ");
        Serial.print(flon);
        Serial.println();
        delay(1000);
    }
}
