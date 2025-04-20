#pragma once

#include "can.h"
#include "mcp2515.h"
#include <stdint.h>
class CanBus {
public:
  CanBus(const uint8_t csPin);
  void begin();
  void send(canid_t id, uint8_t *data, uint8_t length);
  bool read(can_frame &frame);
  
private:
  MCP2515 canBus;

};
