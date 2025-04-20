#include "CanBus.hpp"
#include <Arduino.h>
#include "can.h"

CANBus::CANBus(const uint8_t csPin): canBus(csPin) {
  canBus.reset();
  canBus.setBitrate(CAN_500KBPS, MCP_8MHZ);
  canBus.setNormalMode();
}

void CANBus::send(canid_t id, uint8_t *data, uint8_t length) {
  Serial.println("Sending message");
  can_frame frame;
  frame.can_id = id;
  frame.can_dlc = length;
  for (uint8_t i = 0; i < length; i++) {
    frame.data[i] = data[i];
  }
  canBus.sendMessage(&frame);
}

bool CANBus::read(can_frame &frame) {
  return canBus.readMessage(&frame) == MCP2515::ERROR_OK;
}

