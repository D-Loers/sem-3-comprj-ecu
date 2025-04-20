#include "Headlights.hpp"
#include <Arduino.h>

Headlights::Headlights(uint8_t pin) : pin(pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Headlights::turnOn() {
    digitalWrite(pin, HIGH);
}

void Headlights::turnOff() {
    digitalWrite(pin, LOW);
}
