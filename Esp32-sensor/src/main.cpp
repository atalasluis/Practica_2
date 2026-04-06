#include <WiFi.h>

const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

const char* host = "192.168.1.100"; 
const int port = 5000;

#define TRIG 5
#define ECHO 18

WiFiClient client;

long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracion = pulseIn(ECHO, HIGH);
  long distancia = duracion * 0.034 / 2;

  return distancia;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");

  // Conectar al servidor
  while (!client.connect(host, port)) {
    Serial.println("Conectando al servidor...");
    delay(2000);
  }

  Serial.println("Conectado al servidor");

  // Registrarse como SENSOR
  client.println("SENSOR");
}

void loop() {
  if (!client.connected()) {
    Serial.println("Reconectando...");
    client.connect(host, port);
    client.println("SENSOR");
  }

  long distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.println(distancia);

  // Enviar al servidor
  client.print("DIST:");
  client.println(distancia);

  delay(2000); 
}
