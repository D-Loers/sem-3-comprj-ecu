#pragma once

class IJoystick {
public:
  virtual ~IJoystick() = default;
  virtual int getHorizontal() = 0;
  virtual int getVertical() = 0;
};
