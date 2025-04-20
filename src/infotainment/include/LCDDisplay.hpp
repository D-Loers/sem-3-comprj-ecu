#pragma once

#include "IDisplay.hpp"
#include "LCD-I2C.h"

class LCDDisplay : public IDisplay {
public:
  LCDDisplay();
  void begin();
  void display(const char *message) override;

private:
  LCD_I2C lcd;
};
