#include "CanBusReceiver.hpp"
#include <stdint.h>

CanBusReceiver::CanBusReceiver(CanBus &canBus, IDisplay &display)
    : canBus(canBus), display(display) {}

void CanBusReceiver::update() {
  can_frame frame;
  if (canBus.read(frame)) {
    if (frame.can_id == EngineOverheatID && frame.data[0] == 0x01) {
      uint16_t engineTemp = static_cast<uint16_t>(frame.data[1]);
      char buffer[50];
      sprintf(buffer, "Engine temperature: %d", engineTemp);
    }
    if (frame.can_id == TirePressureID) {
    }
  }
}
