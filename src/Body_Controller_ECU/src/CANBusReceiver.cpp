#include "CANBusReceiver.hpp"
#include <Arduino.h>

CANBusReceiver::CANBusReceiver(CANBus& canBus)
    : canBus(canBus), messageCallback(nullptr) {}

void CANBusReceiver::startTask() {
    xTaskCreate(
        CANBusReceiver::canTask,
        "CANBusTask",
        8192,
        this,
        1,
        nullptr
    );
}

void CANBusReceiver::setMessageCallback(CANMessageCallback callback) {
    messageCallback = callback;
}

void CANBusReceiver::canTask(void* param) {
    CANBusReceiver* receiver = static_cast<CANBusReceiver*>(param);
    can_frame frame;

    for (;;) {
        if (receiver->canBus.read(frame)) {
            receiver->processMessage(frame);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void CANBusReceiver::processMessage(const can_frame& frame) {
    int sourceECU = (frame.can_id >> 5) & 0x7;     // Extract bits 5-7 for source ECU
    int messageType = frame.can_id & 0x1F;        // Extract bits 0-4 for message type

    // Invoke the callback if it's set
    if (messageCallback) {
        messageCallback(sourceECU, messageType, frame.data, frame.can_dlc);
    }
}
