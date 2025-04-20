#pragma once 

class ITaskible {
public:
  virtual ~ITaskible() = default;
  virtual void update() = 0;
};
