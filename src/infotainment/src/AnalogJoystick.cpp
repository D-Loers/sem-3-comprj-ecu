#include "AnalogJoystick.hpp"
#include <Arduino.h>

AnalogJoystick::AnalogJoystick(int xPin, int yPin) : xPin(xPin), yPin(yPin) {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}

int AnalogJoystick::getHorizontal() { return analogRead(xPin); }
int AnalogJoystick::getVertical() { return analogRead(yPin); }
