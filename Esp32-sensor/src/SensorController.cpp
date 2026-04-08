#include "SensorController.h"

SensorController::SensorController(const char* ssid, const char* pass,
                                   const char* host, int port,
                                   int trig, int echo)
    : wifi(ssid, pass),
      tcp(host, port),
      sensor(trig, echo) {}

void SensorController::setup() {
    Serial.begin(115200);

    sensor.init();
    wifi.connect();
    tcp.connect();

    tcp.send("SENSOR");
}

void SensorController::loop() {
    if (!tcp.isConnected()) {
        Serial.println("Reconectando...");
        tcp.connect();
        tcp.send("SENSOR");
    }

    long distancia = sensor.medir();

    Serial.print("Distancia: ");
    Serial.println(distancia);

    tcp.send("DIST:" + String(distancia));

    delay(2000);
}