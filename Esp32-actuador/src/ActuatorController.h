#pragma once
#include "WiFiManager.h"
#include "TCPClient.h"
#include "LEDController.h"

class ActuatorController {
private:
    WiFiManager wifi;
    TCPClient tcp;
    LEDController leds;

public:
    ActuatorController(const char* ssid, const char* pass,
                       const char* host, int port,
                       int r, int y, int g);

    void setup();
    void loop();
};