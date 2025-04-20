#include "CANBusSender.hpp"
#include <Arduino.h>

CANBusSender::CANBusSender(CANBus& canBus) : canBus(canBus) {}

void CANBusSender::sendMessage(int sourceECU, int messageType, const uint8_t* data, uint8_t length) {
    // Construct the arbitration ID (11-bit CAN ID)
    uint32_t arbitrationID = (0b100 << 8) | (sourceECU << 5) | (messageType & 0x1F);  // Mask the messageType to 5 bits

    // Prepare CAN frame
    can_frame frame;
    frame.can_id = arbitrationID; 
    frame.can_dlc = length;       
    memcpy(frame.data, data, length);

    // Send the CAN message
    canBus.send(frame.can_id, frame.data, frame.can_dlc);

    // DEBUGGING
    Serial.print("Sent CAN message: ID = ");
    Serial.print(arbitrationID, HEX);
    Serial.print(", Length = ");
    Serial.println(length);
}
