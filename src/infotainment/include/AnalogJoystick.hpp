#pragma once

#include "IJoystick.hpp"

class AnalogJoystick : public IJoystick {
public:
  AnalogJoystick(int xPin, int yPin);
  int getHorizontal() override;
  int getVertical() override;

private:
  const int xPin;
  const int yPin;
};
