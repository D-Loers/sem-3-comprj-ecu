#include "BodyControllerECU.hpp"
#include <Arduino.h>

BodyControllerECU::BodyControllerECU(CANBus& canBus, CANBusReceiver& canReceiver, IHeadlights& headlights, IBlinker& leftBlinker, IBlinker& rightBlinker)
    : canBus(canBus), canReceiver(canReceiver), headlights(headlights), leftBlinker(leftBlinker), rightBlinker(rightBlinker) {}

void BodyControllerECU::start() {
    // Set up the CAN message callback
    canReceiver.setMessageCallback([this](int sourceECU, int messageType, const uint8_t* data, uint8_t length) {
        this->handleCANMessage(sourceECU, messageType, data, length);
    });

    // Start the CAN receiver task
    canReceiver.startTask();

    Serial.println("BodyControllerECU initialized.");
}

void BodyControllerECU::handleCANMessage(int sourceECU, int messageType, const uint8_t* data, uint8_t length) {
    Serial.printf("Received CAN message: sourceECU=%d, messageType=%d\n", sourceECU, messageType);

    switch (messageType) {
        case HEADLIGHTS_TOGGLE: {
            if (data[0] == 1) {
                Serial.println("Turning on headlights.");
                headlights.turnOn();
            } else {
                Serial.println("Turning off headlights.");
                headlights.turnOff();
            }
            break;
        }
        case USER_INPUT_BLINKERS: {
            uint8_t input = data[0];
            if (input == 0) {
                Serial.println("Turning off both blinkers.");
                leftBlinker.turnOff();
                rightBlinker.turnOff();
            } else if (input == 1) {
                Serial.println("Turning on left blinker.");
                leftBlinker.turnOn();
                rightBlinker.turnOff();
            } else if (input == 2) {
                Serial.println("Turning on right blinker.");
                rightBlinker.turnOn();
                leftBlinker.turnOff();
            }
            break;
        }
        default:
            Serial.println("Unknown message type.");
            break;
    }
}
