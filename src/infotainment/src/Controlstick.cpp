#include "Controlstick.hpp"
#include <Arduino.h>

ControlStick::ControlStick(IJoystick &joystick) : joystick(joystick) {}

void ControlStick::update() {
  HORIZONTAL_EVENT currentEventH = HORIZONTAL_EVENT::NONE;
  VERTICAL_EVENT currentEventV = VERTICAL_EVENT::NONE;
  int x = joystick.getHorizontal();
  int y = joystick.getVertical();

  if (x > 575) {
    currentEventH = HORIZONTAL_EVENT::LEFT;
  } else if (x < 450) {
    currentEventH = HORIZONTAL_EVENT::RIGHT;
  }

  if (y > 575) {
    currentEventV = VERTICAL_EVENT::UP;
  } else if (y < 450) {
    currentEventV = VERTICAL_EVENT::DOWN;
  }

  if (currentEventH != previousEventH && millis() - lastH > debounceDelay) {
    horizontalCallback(currentEventH);
    lastH = millis();
    previousEventH = currentEventH;
  }

  if (currentEventV != previousEventV && millis() - lastV > debounceDelay) {
    verticalCallback(currentEventV);
    lastV = millis();
    previousEventV = currentEventV;
  }
}

void ControlStick::setHorizontalCallback(
    HorizontalCallback horizontalCallback) {
  this->horizontalCallback = horizontalCallback;
}

void ControlStick::setVerticalCallback(VerticalCallback verticalCallback) {
  this->verticalCallback = verticalCallback;
}
