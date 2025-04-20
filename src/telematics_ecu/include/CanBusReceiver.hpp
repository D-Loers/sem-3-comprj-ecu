#pragma once

#include "CANBus.hpp"
#include <functional>
#include <cstdint>
#include "can.h"

class CANBusReceiver {
public:
    using CANMessageCallback = std::function<void(int sourceECU, int messageType, const uint8_t* data, uint8_t length)>;

    CANBusReceiver(CANBus& canBus);
    void startTask(); // Starts the task to poll CAN bus
    void setMessageCallback(CANMessageCallback callback); // Sets the callback for received messages

private:
    static void canTask(void* param); // Task to poll CAN bus
    void processMessage(const can_frame& frame); // Processes a received CAN message

    CANBus& canBus;
    CANMessageCallback messageCallback; // Callback for forwarding messages
};
