#pragma once

class IDisplay {
public:
  virtual ~IDisplay() = default;
  virtual void display(const char *message) = 0;
};

