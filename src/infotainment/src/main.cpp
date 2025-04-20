#include "AnalogJoystick.hpp"
#include "Button.hpp"
#include "CanBusReceiver.hpp"
#include "CanBusSender.hpp"
#include "ControlPanel.hpp"
#include "Controlstick.hpp"
#include "LCDDisplay.hpp"
#include "Potmeter.hpp"
#include "TaskManager.hpp"
#include <Arduino.h>

LCDDisplay display;
CanBus canBus(10);
CanBusSender messageSender(canBus);
CanBusReceiver canBusReceiver(canBus, display);
Button brake(5);
Potmeter throttle(A0);
AnalogJoystick joystick(A1, A2);
ControlStick controlStick(joystick);
ControlPanel controlPanel(messageSender, brake, throttle, controlStick);

void BrakeCallback(BUTTON_EVENT event) {
  controlPanel.brakeCallback(event);
}
void ThrottleCallback(uint8_t value) {
  Serial.println(value);
  controlPanel.throttleCallback(value);
}
void HJoyCallback(HORIZONTAL_EVENT event) {
  controlPanel.horizontalCallback(event);
}
void VJoyCallback(VERTICAL_EVENT event) {
  controlPanel.verticalCallback(event);
}

void setup() {
  brake.setCallback(BrakeCallback);
  throttle.setCallback(ThrottleCallback);
  controlStick.setHorizontalCallback(HJoyCallback);
  controlStick.setVerticalCallback(VJoyCallback);
  Serial.begin(115200);
  display.begin();
  canBus.begin();
}

void loop() {
  canBusReceiver.update();
  brake.update();
  throttle.update();
  controlStick.update();
}
