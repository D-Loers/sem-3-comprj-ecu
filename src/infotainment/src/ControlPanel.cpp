#include "ControlPanel.hpp"
ControlPanel::ControlPanel(IMessageSender &messageSender, Button &brake,
                           Potmeter &throttle, ControlStick &controlStick)
    : messageSender(messageSender), brake(brake), throttle(throttle),
      controlStick(controlStick) {}

void ControlPanel::brakeCallback(BUTTON_EVENT event) {
  switch (event) {
  case BUTTON_EVENT::PRESSED:
    messageSender.sendBrakeMessage(true);
    break;
  case BUTTON_EVENT::RELEASED:
    messageSender.sendBrakeMessage(false);
    break;
  }
}

void ControlPanel::throttleCallback(int value) {
  messageSender.sendThrottleMessage(value);
}

void ControlPanel::horizontalCallback(HORIZONTAL_EVENT event) {
  switch (event) {
  case HORIZONTAL_EVENT::LEFT:
    messageSender.sendBlinkerMessage(1);
    break;
  case HORIZONTAL_EVENT::RIGHT:
    messageSender.sendBlinkerMessage(2);
    break;
  case HORIZONTAL_EVENT::NONE:
    messageSender.sendBlinkerMessage(0);
    break;
  }
}

void ControlPanel::verticalCallback(VERTICAL_EVENT event) {
  switch (event) {
  case VERTICAL_EVENT::UP:
    messageSender.sendHeadlightMessage(true);
    break;
  case VERTICAL_EVENT::DOWN:
    messageSender.sendHeadlightMessage(false);
    break;
  case VERTICAL_EVENT::NONE:
    break;
  }
}
