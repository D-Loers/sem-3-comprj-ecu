#pragma once

#include "WebSocket.hpp"
#include "CANBus.hpp"
#include "CANBusReceiver.hpp"
#include "CANBusSender.hpp"
#include "ArduinoJson.h"

class TelematicsECU {
public:
    TelematicsECU(const char* serverIP, int keepAliveInterval, uint8_t canCSPin);
    ~TelematicsECU();
    void start();

private:
    void onWebsocketReceiveCallback(const char* msg); // Handles WebSocket messages
    void onCANMessageReceived(int sourceECU, int messageType, const uint8_t* data, uint8_t length);

    WebSocket& ws;
    CANBus canBus;
    CANBusReceiver canReceiver;
    CANBusSender canSender;
};
