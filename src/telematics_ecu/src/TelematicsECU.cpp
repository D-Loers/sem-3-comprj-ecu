#include "TelematicsECU.hpp"
#include <Arduino.h>

TelematicsECU::TelematicsECU(const char* serverIP, int keepAliveInterval, uint8_t canCSPin)
    : ws(WebSocket::getInstance(serverIP)),
      canBus(canCSPin),
      canReceiver(canBus),
      canSender(canBus) {

    // Set WebSocket callback for receiving messages
    ws.onReceive([this](const char* msg) {
        this->onWebsocketReceiveCallback(msg);
    });

    // Set CAN message callback for receiving CAN messages
    canReceiver.setMessageCallback([this](int sourceECU, int messageType, const uint8_t* data, uint8_t length) {
        this->onCANMessageReceived(sourceECU, messageType, data, length);
    });
}

TelematicsECU::~TelematicsECU() = default;

void TelematicsECU::start() {
    // Start WebSocket and CAN tasks
    ws.startTask();
    canReceiver.startTask();
}

void TelematicsECU::onWebsocketReceiveCallback(const char* msg) {
    // Unpack JSON message
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, msg);
    
    if (error) {
        Serial.print("Failed to parse WebSocket message: ");
        Serial.println(error.f_str());
        return;
    }

    // Extract the sourceECU, messageType, and data from the JSON
    int messageType = doc["messageType"];
    JsonArray dataArray = doc["data"];

    // Convert the data array to a byte array
    uint8_t data[dataArray.size()];
    for (size_t i = 0; i < dataArray.size(); i++) {
        data[i] = dataArray[i];
    }

    // Construct and send the CAN message (Source ECU hardcoded to telematics ECU code)
    canSender.sendMessage(0b110, messageType, data, sizeof(data));
    Serial.println("Forwarded WebSocket message to CAN Bus");
}

void TelematicsECU::onCANMessageReceived(int sourceECU, int messageType, const uint8_t* data, uint8_t length) {
    // Forward the CAN message to the WebSocket
    JsonDocument doc;
    doc["sourceECU"] = sourceECU;
    doc["messageType"] = messageType;
    JsonArray dataArray = doc.createNestedArray("data");
    
    // Add the data to the JSON array
    for (uint8_t i = 0; i < length; ++i) {
        dataArray.add(data[i]);
    }

    // Serialize the JSON document into a string and send it over WebSocket
    char jsonBuffer[256];
    serializeJson(doc, jsonBuffer);
    ws.send(jsonBuffer);

    Serial.print("Forwarded CAN message to WebSocket: ");
    Serial.println(jsonBuffer);
}
