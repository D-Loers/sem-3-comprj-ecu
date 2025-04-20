#pragma once

#include "IJoystick.hpp"
#include "ITaskible.hpp"

enum class HORIZONTAL_EVENT { LEFT, RIGHT, NONE };
enum class VERTICAL_EVENT { UP, DOWN, NONE };

using HorizontalCallback = void (*)(HORIZONTAL_EVENT);
using VerticalCallback = void (*)(VERTICAL_EVENT);

class ControlStick : public ITaskible {
public:
  ControlStick(IJoystick &joystick);
  void update() override;
  void setHorizontalCallback(HorizontalCallback horizontalCallback);
  void setVerticalCallback(VerticalCallback verticalCallback);

private:
  IJoystick &joystick;
  const unsigned long debounceDelay = 50;
  unsigned long lastH;
  unsigned long lastV;
  HORIZONTAL_EVENT previousEventH = HORIZONTAL_EVENT::NONE;
  VERTICAL_EVENT previousEventV = VERTICAL_EVENT::NONE;
  HorizontalCallback horizontalCallback;
  VerticalCallback verticalCallback;
};
