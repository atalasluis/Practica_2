#include <WiFi.h>

const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

const char* host = "192.168.1.100"; 
const int port = 5000;

#define LED_RED 5
#define LED_YELLOW 18
#define LED_GREEN 19

WiFiClient client;

void apagarTodos() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");

  while (!client.connect(host, port)) {
    Serial.println("Conectando al servidor...");
    delay(2000);
  }

  Serial.println("Conectado al servidor");

  client.println("ACTUADOR");
}

void loop() {
  if (!client.connected()) {
    Serial.println("Reconectando...");
    client.connect(host, port);
    client.println("ACTUADOR");
  }

  if (client.available()) {
    String comando = client.readStringUntil('\n');
    comando.trim();

    Serial.print("Comando recibido: ");
    Serial.println(comando);

    apagarTodos();

    if (comando == "RED") {
      digitalWrite(LED_RED, HIGH);
    }
    else if (comando == "YELLOW") {
      digitalWrite(LED_YELLOW, HIGH);
    }
    else if (comando == "GREEN") {
      digitalWrite(LED_GREEN, HIGH);
    }
  }
}