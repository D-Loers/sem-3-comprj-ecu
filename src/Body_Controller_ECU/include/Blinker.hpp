#pragma once

#include "IBlinker.hpp"
#include <Arduino.h>

class Blinker : public IBlinker {
public:
    Blinker(uint8_t pin);
    ~Blinker();

    void turnOn() override;
    void turnOff() override;

private:
    static void blinkTask(void* param);

    uint8_t pin;
    bool state;
    TaskHandle_t blinkTaskHandle;
};
