#include "CANBusSender.hpp"
#include <Arduino.h>

CANBusSender::CANBusSender(CANBus& canBus) : canBus(canBus) {}

void CANBusSender::sendTirePressureUpdate(float tire1Pressure){
    can_frame frame;
    frame.can_id = 0b01101010001;   // As specified in protocol design
    frame.can_dlc = 2;

    // Scale float into a 2 bit integer
    uint16_t packedTire1Pressure = ((tire1Pressure - 10) / (45-10) * 65535);
    frame.data[0] = packedTire1Pressure & 0xFF;
    frame.data[1] = (packedTire1Pressure >> 8) & 0xFF;

    canBus.send(frame.can_id, frame.data, frame.can_dlc);
    Serial.println("Sent update");
}

void CANBusSender::sendTirePressureWarning(void){
    can_frame frame;
    frame.can_id = 0b01101010000;   // As specified in protocol design
    frame.can_dlc = 2;
    frame.data[0] = 1;
    frame.data[1] = 1;
    canBus.send(frame.can_id, frame.data, frame.can_dlc);
    Serial.println("Sent WARNING");
}