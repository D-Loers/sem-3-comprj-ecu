#include "NetworkManager.hpp"

#include <Arduino.h>

/* ------ Constructor ------ */

NetworkManager::NetworkManager(IReceiver &receiver, QueueHandle_t &networkToMediatorQueue) 
    : receiver(receiver), networkToMediatorQueue(networkToMediatorQueue) {}

/* ------ Public methods ------ */

void NetworkManager::Run(void) {
    if (this->receiver.IsMessageAvailable()) {
        can_frame receivedMessage;

        if (this->receiver.GetMessage(receivedMessage)) {
            xQueueSend(this->networkToMediatorQueue, &receivedMessage, portMAX_DELAY);
        }
    }
}