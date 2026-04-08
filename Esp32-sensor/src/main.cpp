#include "SensorController.h"

#define TRIG 26
#define ECHO 25

SensorController controller(
    "TP-Link_22C2", "*",     // WiFi
    "192.168.0.107", 12345, // servidor
    TRIG, ECHO
);

void setup() {
    controller.setup();
}

void loop() {
    controller.loop();
}