#include "CanBus.hpp"
#include "can.h"
#include <Arduino.h>
CanBus::CanBus(const uint8_t csPin) : canBus(csPin) {}

void CanBus::begin() {
  canBus.reset();
  canBus.setBitrate(CAN_500KBPS, MCP_8MHZ);
  canBus.setNormalMode();
}

void CanBus::send(canid_t id, uint8_t *data, uint8_t length) {
  can_frame frame;
  frame.can_id = id;
  frame.can_dlc = length;
  for (uint8_t i = 0; i < length; i++) {
    frame.data[i] = data[i];
  }
  canBus.sendMessage(&frame);
}

bool CanBus::read(can_frame &frame) {
  return canBus.readMessage(&frame) == MCP2515::ERROR_OK;
}
