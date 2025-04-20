#include "CanBusSender.hpp"
CanBusSender::CanBusSender(CanBus &canBus) : canBus(canBus) {}

void CanBusSender::sendHeadlightMessage(uint8_t value) {
  canBus.send(headlightID, &value, 1);
}

void CanBusSender::sendBlinkerMessage(uint8_t value) {
  canBus.send(blinkerID, &value, 1);
}

void CanBusSender::sendBrakeMessage(uint8_t value) {
  canBus.send(brakeID, &value, 1);
}

void CanBusSender::sendThrottleMessage(uint8_t value) {
  canBus.send(throttleID, &value, 1);
}
