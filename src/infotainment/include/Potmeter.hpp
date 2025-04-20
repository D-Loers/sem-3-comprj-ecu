#pragma once

#include "ITaskible.hpp"
#include <stdint.h>

using PotMeterCallback = void (*)(uint8_t);

class Potmeter : public ITaskible {
public:
  Potmeter(int pin);
  void update() override;
  void setCallback(PotMeterCallback potMeterCallback);

private:
  PotMeterCallback potmeterCallback;
  const int pin;
  const unsigned long pollDelay = 200;
  unsigned long lastPollTime = 0;
  uint8_t lastPotmeterValue;
};
