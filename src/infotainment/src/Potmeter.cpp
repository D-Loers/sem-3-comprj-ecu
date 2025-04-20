#include "Potmeter.hpp"
#include <Arduino.h>

Potmeter::Potmeter(int pin) : pin(pin) {
  pinMode(pin, INPUT);
  lastPotmeterValue = analogRead(pin);
}

void Potmeter::update() {
  uint8_t potmeterValue = analogRead(pin);
  if (millis() - lastPollTime > pollDelay) {
    lastPollTime = millis();
    if (potmeterValue != lastPotmeterValue) {
      potmeterCallback(potmeterValue);
      lastPotmeterValue = potmeterValue;
    }
  }
}

void Potmeter::setCallback(PotMeterCallback potmeterCallback) {
  this->potmeterCallback = potmeterCallback;
}
