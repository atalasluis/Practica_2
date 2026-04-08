#include "ActuatorController.h"

#define RED_PIN 19
#define YELLOW_PIN 18
#define GREEN_PIN 5

ActuatorController controller(
    "TP-Link_22C2", "*",     // WiFi
    "192.168.0.107", 12345, // servidor
    RED_PIN, YELLOW_PIN, GREEN_PIN
);

void setup() {
    controller.setup();
}

void loop() {
    controller.loop();
}