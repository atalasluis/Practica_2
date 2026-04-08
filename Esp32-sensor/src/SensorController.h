#pragma once
#include "WiFiManager.h"
#include "TCPClient.h"
#include "UltrasonicSensor.h"

class SensorController {
private:
    WiFiManager wifi;
    TCPClient tcp;
    UltrasonicSensor sensor;

public:
    SensorController(const char* ssid, const char* pass,
                     const char* host, int port,
                     int trig, int echo);

    void setup();
    void loop();
};