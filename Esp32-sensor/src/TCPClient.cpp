#include "TCPClient.h"

TCPClient::TCPClient(const char* host, int port)
    : host(host), port(port) {}

void TCPClient::connect() {
    while (!client.connect(host, port)) {
        Serial.println("Conectando al servidor...");
        delay(2000);
    }

    Serial.println("Conectado al servidor");
}

bool TCPClient::isConnected() {
    return client.connected();
}

void TCPClient::send(const String& msg) {
    client.println(msg);
}