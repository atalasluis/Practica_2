#pragma once
#include <Arduino.h>

class LEDController {
private:
    int redPin;
    int yellowPin;
    int greenPin;

    String currentMode;
    unsigned long lastBlink;
    bool blinkState;

public:
    LEDController(int r, int y, int g);

    void init();
    void setColor(String color);
    void update(); // para parpadeo
};