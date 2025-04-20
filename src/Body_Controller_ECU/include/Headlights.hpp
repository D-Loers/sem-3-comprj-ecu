#pragma once

#include "IHeadlights.hpp"
#include "Arduino.h"

class Headlights : public IHeadlights {
public:
    Headlights(uint8_t pin);
    void turnOn() override;
    void turnOff() override;

private:
    uint8_t pin;
};
