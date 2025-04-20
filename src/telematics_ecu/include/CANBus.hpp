#pragma once

#include "can.h"
#include "mcp2515.h"
#include <cstdint>

class CANBus {
public:
  CANBus(const uint8_t csPin);
  void send(canid_t id, uint8_t *data, uint8_t length);
  bool read(can_frame &frame);
  
private:
  MCP2515 canBus;
};
