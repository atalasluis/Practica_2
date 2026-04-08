# Proyecto IoT con ESP32 y Servidor TCP

Este proyecto implementa un sistema IoT utilizando dos módulos ESP32 comunicados de forma inalámbrica mediante sockets TCP y un servidor central en Python.

## Descripción

El sistema está compuesto por:

* Un ESP32 con sensor ultrasónico que mide distancia y envía los datos al servidor.
* Un ESP32 con LEDs que actúa como sistema de respuesta (actuador).
* Un servidor TCP en Python que recibe los datos del sensor, los procesa y envía comandos al actuador.

## 1. Requerimientos Funcionales y No Funcionales

### Funcionales

* El sistema debe permitir que múltiples clientes (2 clientes: un sensor y un actuador) se conecten al servidor mediante comunicación TCP.
* El sistema debe permitir que los clientes se identifiquen como: `"SENSOR"` y `"ACTUADOR"`.
* El sistema debe recibir datos enviados por el ESP32 sensor en el formato: `DIST:<valor>`.
* El servidor debe procesar los datos de distancia recibidos y determinar una acción según la lógica definida.
* El sistema debe enviar comandos al ESP32 actuador según la lógica:

        DANGER → distancia < 10
        RED → 10 ≤ distancia < 20
        YELLOW → 20 ≤ distancia < 50
        GREEN → 50 ≤ distancia < 80

* El ESP32 actuador debe recibir los comandos y activar la combinación de LEDs correspondiente.
  
### No Funcionales

* El sistema debe procesar y responder a los datos del sensor en tiempo cercano a tiempo real (≈2 segundos debido al intervalo de envío del sensor) 
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

  | Tipo de Mensaje | Emisor   | Formato        | Ejemplo   | Descripción                      |
   |-----------------|----------|----------------|-----------|----------------------------------|
   | Identificación  | ESP32    | `"SENSOR"`     | SENSOR    | Registro como sensor             |
   | Identificación  | ESP32    | `"ACTUADOR"`   | ACTUADOR  | Registro como actuador           |
   | Datos           | Sensor   | `DIST:<valor>` | DIST:30   | Envío de distancia               |
   | Respuesta       | Servidor | `"DANGER"`     | DANGER    | Estado crítico                   |
   | Respuesta       | Servidor | `"RED"`        | RED       | Distancia corta                  |
   | Respuesta       | Servidor | `"YELLOW"`     | YELLOW    | Distancia media                  |
   | Respuesta       | Servidor | `"GREEN"`      | GREEN     | Distancia segura                 |

  | Distancia (cm) | Estado           | Acción (LEDs)              |
   |---------------|-----------------|----------------------------|
   | < 10          | Estado crítico  | Parpadeo (todos ON/OFF)    |
   | 10 – 19       | Distancia corta | Activación combinada       |
   | 20 – 49       | Distancia media | Activación combinada       |
   | 50 – 79       | Distancia segura| Activación combinada       |

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
* **Resultado esperado:** El servidor detecta la desconexión y cierra la conexión

#### ⚠️ CP7 – Datos inválidos

* **Entrada:** "DIST:abc"  
* **Resultado esperado:** El sistema genera una excepción (no controlada)

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
* Procesamiento correcto de datos válidos
* Respuesta adecuada del actuador
* Procesamiento correcto de mensajes concatenados

---

## 5. Resultados

* Comunicación TCP funcional.
* Manejo concurrente de clientes mediante hilos.
* Procesamiento correcto de datos válidos.
* Respuestas correctas según distancia.
* Sistema funcional en pruebas reales.
---

## 6. Conclusiones

* TCP garantiza comunicación confiable.
* Arquitectura cliente-servidor simplifica el sistema.
* Separación de responsabilidades mejora mantenimiento.
* Uso de hilos permite concurrencia básica.
* Sistema cumple requisitos funcionales y no funcionales.

---

## 7. Recomendaciones

* Usar JSON o MQTT.
* Implementar logs.
* Migrar a `asyncio`.
* Añadir autenticación.
* Integrar base de datos.
* Crear dashboard web.

---

## 8. Anexos

### Flujo de comunicación
ESP32 Sensor        →   Servidor TCP       →   ESP32 Actuador
   |                        |                        |
   |---- "SENSOR" --------->|                        |
   |                        |                        |
   |---- "DIST:30" -------->|                        |
   |                        |---- "YELLOW" --------->|
   |                        |                        |
---

### Ejemplo de mensajes
#### Registro de cliente:

SENSOR
ACTUADOR

#### Envío de datos:

DIST:10
DIST:30
DIST:60

#### Respuestas del servidor:

RED
YELLOW
GREEN

---

### Consideraciones TCP

* Protocolo orientado a conexión
* Puede concatenar mensajes
* Requiere procesamiento manual del buffer

---

### Mejora con JSON

```json
{
  "type": "sensor",
  "distance": 30
}
```
### Respuesta:

```json
{
  "action": "YELLOW"
}
```