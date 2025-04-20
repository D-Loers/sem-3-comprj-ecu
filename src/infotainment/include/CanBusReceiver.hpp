#pragma once

#include "CanBus.hpp"
#include "IDisplay.hpp"
#include "ITaskible.hpp"

class CanBusReceiver : public ITaskible {
public:
  CanBusReceiver(CanBus &canBus, IDisplay &display);
  void update() override;

private:
  CanBus &canBus;
  IDisplay &display;
  const canid_t EngineOverheatID = 0b00100000011 ;
  const canid_t TirePressureID = 0b01101010000;
};
