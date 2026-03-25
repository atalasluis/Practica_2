# Proyecto IoT con ESP32 y Servidor TCP

Este proyecto implementa un sistema IoT utilizando dos módulos ESP32 comunicados de forma inalámbrica mediante sockets TCP y un servidor central en Python.

## Descripción

El sistema está compuesto por:

* Un ESP32 con sensor ultrasónico que mide distancia y envía los datos al servidor.
* Un ESP32 con LEDs que actúa como sistema de respuesta (actuador).
* Un servidor TCP en Python que recibe los datos del sensor, los procesa y envía comandos al actuador.

## Funcionamiento

1. El ESP32 sensor captura la distancia.
2. Envía la información al servidor mediante WiFi.
3. El servidor procesa los datos y determina una acción.
4. El ESP32 actuador recibe el comando y enciende el LED correspondiente.

## Tecnologías utilizadas

* ESP32 (Framework Arduino - PlatformIO)
* Python (Sockets TCP)
* Comunicación WiFi

## Estructura del proyecto

* `esp32_sensor/` → Código del ESP32 con sensor ultrasónico
* `esp32_actuador/` → Código del ESP32 con LEDs
* `server_python/` → Servidor TCP en Python

## Objetivo

Demostrar la comunicación cliente-servidor en sistemas embebidos y el control de actuadores en función de datos capturados en tiempo real.
