#pragma once
#include <WiFi.h>

class TCPClient {
private:
    const char* host;
    int port;
    WiFiClient client;

public:
    TCPClient(const char* host, int port);

    void connect();
    bool isConnected();

    void send(const String& msg);
    String receive();   // 🔥 NUEVO
};