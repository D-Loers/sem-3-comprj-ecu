#pragma once

#include "IMessageSender.hpp"
#include "CANBus.hpp"
#include "can.h"

class CANBusSender : public IMessageSender{
public:
    CANBusSender(CANBus& canBus);
    void sendTirePressureUpdate(float) override;
    void sendTirePressureWarning(void) override;

private:
    CANBus& canBus;
};
