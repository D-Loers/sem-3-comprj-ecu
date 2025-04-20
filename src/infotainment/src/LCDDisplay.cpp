#include "LCDDisplay.hpp"
#include "Wire.h"
#include <Arduino.h>

LCDDisplay::LCDDisplay() : lcd(0x27, 16, 2) {}

void LCDDisplay::begin() {
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
}

void LCDDisplay::display(const char *message) {
  Serial.println(message);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}
