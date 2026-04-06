# Proyecto IoT con ESP32 y Servidor TCP

Este proyecto implementa un sistema IoT utilizando dos módulos ESP32 comunicados de forma inalámbrica mediante sockets TCP y un servidor central en Python.

## Descripción

El sistema está compuesto por:

* Un ESP32 con sensor ultrasónico que mide distancia y envía los datos al servidor.
* Un ESP32 con LEDs que actúa como sistema de respuesta (actuador).
* Un servidor TCP en Python que recibe los datos del sensor, los procesa y envía comandos al actuador.

## 1. Requerimientos Funcionales y No Funcionales

### Funcionales

* El sistema debe permitir que múltiples clientes (ESP32 o simuladores) se conecten al servidor mediante comunicación TCP.
* El sistema debe permitir que los clientes se identifiquen como: SENSOR y ACTUADOR.
* El sistema debe recibir datos enviados por el ESP32 sensor en el formato: DIST:<valor>
* El servidor debe procesar los datos de distancia recibidos y determinar una acción según la lógica definida.
* El sistema debe enviar comandos al ESP32 actuador según la lógica:

        RED → distancia < 20 

        YELLOW → 20 ≤ distancia < 50 

        GREEN → distancia ≥ 50 

* El ESP32 actuador debe recibir los comandos y activar el LED correspondiente.
  
### No Funcionales

* El sistema debe procesar y responder a los datos del sensor en tiempo real (latencia mínima).
* La comunicación entre clientes y servidor debe ser confiable, garantizando la entrega de mensajes mediante TCP.
* El sistema debe ser fácil de probar mediante herramientas como scripts en Python.

---

## 2. Diseño del Sistema
### Diagrama de bloques

### Diagrama de circuito

![Diagrama de circuito](/static/Diagrama%20esquemático%20de%20circuitos%20ESP32.png)

### Diagrama de arquitectura del sistema

![Diagrama de circuito](/static/architecture%20P2.png)

### Especificación del protocolo de aplicación
  
  1. ESP32 → se conecta al servidor (TCP)
  2. ESP32 → envía identificación
     "SENSOR" o "ACTUADOR"

  3. Sensor → envía datos
     "DIST:30"

  4. Servidor:
     - recibe datos
     - procesa lógica

  5. Servidor → envía comando
     "YELLOW"

  6. Actuador → enciende LED correspondiente

  | Tipo de Mensaje | Emisor | Formato | Ejemplo | Descripcion |
  | --------------- |------- | ------- | ------- | ----------- |
  | Identificacion | ESP32 | Sensor | Sensor | Se registra como sensor |
  | Identificacion | ESP32 | Actuador | Actuador | Se registra como actuador |
  | Datos | Sensor | DIST:<valor> | DIST:25 | Envía distancia |
  | Respuesta | Servidor | RED | RED | LED rojo |
  | Respuesta | Servidor | YELLOW | YELLOW | LED amarillo |
  | Respuesta | Servidor | GREEN | GREEN | LED verde |

  | Distancia (cm) | Accion | Led |
  | -------------- | ------ | --- |
  | < 20 | Muy cerca | Rojo |
  | < 50 | Medio | Amarillo |
  | < 80 | Lejos | Verde |

### Diagramas estructurales y de comportamiento

#### Diagramas Estructurales

* Diagrama de Componentes
  
![Diagrama de Componentes](/static/mermaid-diagram.png)

* Diagrama de Clases (Servidor Python)
  
![Diagrama de Clases](/static/mermaid-diagram(1).png)

#### Diagramas de Comportamiento

* Diagrama de Secuencia

![Diagrama de Secuencia](/static/mermaid-diagram(2).png)

* Diagrama de Flujo del Sistema
  
![Diagrama de Flujo del Sistema](/static/mermaid-diagram(3).png)

* Diagrama de Estados (Actuador)
  
![Diagrama de Estados](/static/mermaid-diagram(4).png)

* Diagrama de Estados (Sensor)
  
![Diagrama de Estados](/static/mermaid-diagram(5).png)

---

## 3. Implementación

### Funcionamiento

1. El ESP32 sensor captura la distancia.
2. Envía la información al servidor (TCP) mediante WiFi.
3. El servidor procesa los datos y determina una acción.
4. El ESP32 actuador recibe el comando y enciende el LED correspondiente.

### Tecnologías utilizadas

* ESP32 (Framework Arduino - PlatformIO)
* Python (Sockets TCP)
* Comunicación WiFi

### Estructura del proyecto

* `esp32_sensor/` → Código del ESP32 con sensor ultrasónico
* `esp32_actuador/` → Código del ESP32 con LEDs
* `server_python/` → Servidor TCP en Python

---

## 4. Pruebas y Validaciones

El plan de pruebas cubre:

* Conexión de clientes (ESP32 y simuladores) al servidor
* Envío de datos desde el sensor
* Procesamiento lógico en el servidor
* Recepción y ejecución de comandos en el actuador
* Manejo de errores y desconexiones

### Componentes del sistema

| Componente        | Descripción                       |
| ----------------- | --------------------------------- |
| ESP32 Sensor      | Envía datos de distancia          |
| ESP32 Actuador    | Recibe comandos y activa LEDs     |
| Servidor Python   | Procesa datos y coordina acciones |
| Scripts de prueba | Simulan sensor o actuador         |

### Casos de prueba

#### ✅ CP1 – Conexión de cliente sensor

* **Entrada:** "SENSOR"
* **Resultado esperado:** El servidor registra el sensor correctamente

#### ✅ CP2 – Conexión de cliente actuador

* **Entrada:** "ACTUADOR"
* **Resultado esperado:** El servidor registra el actuador correctamente

#### ✅ CP3 – Envío de datos válidos

| Entrada | Resultado esperado |
| ------- | ------------------ |
| DIST:10 | RED                |
| DIST:30 | YELLOW             |
| DIST:60 | GREEN              |

#### ✅ CP4 – Comunicación completa

* Sensor envía datos
* Servidor procesa
* Actuador recibe comando

**Resultado esperado:** Flujo completo sin errores

#### ⚠️ CP5 – Mensajes concatenados (TCP)

* **Entrada:** "SENSOR\nDIST:10"
* **Resultado esperado:** Ambos mensajes procesados correctamente

#### ⚠️ CP6 – Desconexión del cliente

* Cliente se desconecta
* **Resultado esperado:** El servidor detecta y maneja la desconexión

#### ⚠️ CP7 – Datos inválidos

* **Entrada:** "DIST:abc"
* **Resultado esperado:** Error controlado sin caída del servidor

### Metodología de pruebas

Se utilizaron tres tipos de pruebas:

#### 🔹 Pruebas simuladas

Uso de scripts Python:

* `test_sensor.py`
* `test_actuador.py`

#### 🔹 Pruebas híbridas

* ESP32 real + script Python

#### 🔹 Pruebas reales

* ESP32 sensor + ESP32 actuador

### Resultados obtenidos

* Comunicación TCP estable
* Procesamiento correcto de datos
* Respuesta adecuada del actuador
* Corrección de errores en manejo de mensajes TCP

---

## 5. Resultados

---

## 6. Conclusiones

---

## 7. Recomendaciones

---

## 8. Anexos