#include "ActuatorController.h"

ActuatorController::ActuatorController(const char* ssid, const char* pass,
                                       const char* host, int port,
                                       int r, int y, int g)
    : wifi(ssid, pass),
      tcp(host, port),
      leds(r, y, g) {}

void ActuatorController::setup() {
    Serial.begin(115200);

    leds.init();
    wifi.connect();
    tcp.connect();

    tcp.send("ACTUADOR");
}

void ActuatorController::loop() {

    if (!tcp.isConnected()) {
        Serial.println("Reconectando...");
        tcp.connect();
        tcp.send("ACTUADOR");
    }

    String comando = tcp.receive();

    if (comando.length() > 0) {
        comando.trim();

        Serial.print("Comando recibido: ");
        Serial.println(comando);

        leds.setColor(comando);
    }

    // IMPORTANTE
    leds.update();
}