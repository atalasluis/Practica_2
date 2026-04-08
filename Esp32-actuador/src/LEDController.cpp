#include "LEDController.h"

LEDController::LEDController(int r, int y, int g)
    : redPin(r), yellowPin(y), greenPin(g),
      currentMode("OFF"), lastBlink(0), blinkState(false) {}

void LEDController::init() {
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);

    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
}

// Configura modo
void LEDController::setColor(String color) {

    currentMode = color;

    if (color == "GREEN") {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, LOW);
    }
    else if (color == "YELLOW") {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, LOW);
    }
    else if (color == "RED") {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, HIGH);
    }
    else if (color == "DANGER") {
        // No encendemos fijo → lo maneja update()
        lastBlink = millis();
        blinkState = false;
    }
}

// Se llama en loop()
void LEDController::update() {

    if (currentMode == "DANGER") {

        if (millis() - lastBlink > 300) {
            lastBlink = millis();
            blinkState = !blinkState;

            digitalWrite(redPin, blinkState);
            digitalWrite(yellowPin, blinkState);
            digitalWrite(greenPin, blinkState);
        }
    }
}