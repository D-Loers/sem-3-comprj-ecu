#pragma once

#include "CanBus.hpp"
#include "IMessageSender.hpp"
#include "can.h"

class CanBusSender : public IMessageSender {
public:
  CanBusSender(CanBus &canBus);
  void sendHeadlightMessage(uint8_t) override;
  void sendBlinkerMessage(uint8_t) override;
  void sendBrakeMessage(uint8_t) override;
  void sendThrottleMessage(uint8_t) override;

private:
  CanBus &canBus;
  const canid_t headlightID = 0b00100000011;
  const canid_t blinkerID = 0b10101110100;
  const canid_t brakeID = 0b10101110101;
  const canid_t throttleID = 0b11001111001;
};
