#pragma once

#include "Button.hpp"
#include "Controlstick.hpp"
#include "IMessageSender.hpp"
#include "Potmeter.hpp"
class ControlPanel {
public:
  ControlPanel(IMessageSender &messageSender, Button &brake, Potmeter &throttle,
               ControlStick &controlStick);
  void brakeCallback(BUTTON_EVENT event);
  void throttleCallback(int value);
  void horizontalCallback(HORIZONTAL_EVENT event);
  void verticalCallback(VERTICAL_EVENT event);

private:
  IMessageSender &messageSender;
  Button &brake;
  Potmeter &throttle;
  ControlStick &controlStick;
};
