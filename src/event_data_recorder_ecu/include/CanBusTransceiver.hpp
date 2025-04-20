#pragma once

#include <SPI.h>
#include <mcp2515.h>
#include "ITransmitter.hpp"
#include "IReceiver.hpp"
#include <Arduino.h>

class CANBusTransceiver : public IReceiver, public ITransmitter {
public:
    CANBusTransceiver();
    ~CANBusTransceiver();
    bool SendMessage(const can_frame &) override;
    bool IsMessageAvailable(void) override;
    bool GetMessage(can_frame &) override;

private:
    const int kSCLKPin = 18;
    const int kMISOPin = 19;
    const int kMOSIPin = 23;
    const int kSSPin = 5;
    SPIClass vspi;
    MCP2515 *CANBus;
};
