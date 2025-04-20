#pragma once
#include <stdint.h>

class IMessageSender {
public:
  virtual ~IMessageSender() = default;
  virtual void sendHeadlightMessage(uint8_t) = 0;
  virtual void sendBlinkerMessage(uint8_t) = 0;
  virtual void sendBrakeMessage(uint8_t) = 0;
  virtual void sendThrottleMessage(uint8_t) = 0;
};
