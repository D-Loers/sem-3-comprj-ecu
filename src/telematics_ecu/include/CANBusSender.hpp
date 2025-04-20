#pragma once

#include "CANBus.hpp"
#include "can.h"

class CANBusSender {
public:
    CANBusSender(CANBus& canBus);
    void sendMessage(int sourceECU, int messageType, const uint8_t* data, uint8_t length);

private:
    CANBus& canBus;
};
