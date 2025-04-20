#include "Button.hpp"
#include <Arduino.h>

Button::Button(int pin) : pin(pin) {
  pinMode(pin, INPUT);
  lastButtonState = digitalRead(pin);
}

void Button::update() {
  int buttonState = digitalRead(pin);

  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState != currentState) {
      currentState = buttonState;
      BUTTON_EVENT event =
          buttonState == HIGH ? BUTTON_EVENT::PRESSED : BUTTON_EVENT::RELEASED;
      buttonCallback(event);
    }
  }

  lastButtonState = buttonState;
}

void Button::setCallback(ButtonCallback buttonCallback) {
  this->buttonCallback = buttonCallback;
}
