#pragma once

#include "CANBus.hpp"
#include "CANBusReceiver.hpp"
#include "IHeadlights.hpp"
#include "IBlinker.hpp"
#include "EMessageType.hpp"

class BodyControllerECU {
public:
    // Constructor
    BodyControllerECU(CANBus& canBus, CANBusReceiver& canReceiver, IHeadlights& headlights, IBlinker& leftBlinker, IBlinker& rightBlinker);

    // Starts the ECU, initializes tasks and sets up the CAN callback
    void start();

private:
    // Handles incoming CAN messages
    void handleCANMessage(int sourceECU, int messageType, const uint8_t* data, uint8_t length);

    // Member variables
    CANBus& canBus;
    CANBusReceiver& canReceiver;
    IHeadlights& headlights;
    IBlinker& leftBlinker;
    IBlinker& rightBlinker;
};
