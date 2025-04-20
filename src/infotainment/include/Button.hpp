#pragma once

#include "ITaskible.hpp"

enum class BUTTON_EVENT { PRESSED, RELEASED };

using ButtonCallback = void (*)(BUTTON_EVENT);

class Button : public ITaskible {
public:
  Button(int pin);
  void update() override;
  void setCallback(ButtonCallback buttonCallback);

private:
  ButtonCallback buttonCallback;
  const int pin;
  const unsigned long debounceDelay = 50;
  unsigned long lastDebounceTime = 0;
  int lastButtonState;
  int currentState;
};
