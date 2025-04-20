#include "Mediator.hpp"

#include <Arduino.h>

/* ------ Constructor ------ */

Mediator::Mediator(QueueHandle_t &networkToMediatorQueue, QueueHandle_t &mediatorToStorageQueue)
    : networkToMediatorQueue(networkToMediatorQueue), mediatorToStorageQueue(mediatorToStorageQueue) {}

/* ------ Public methods ------ */

void Mediator::Run(void) {
    if (uxQueueMessagesWaiting(this->networkToMediatorQueue) != 0) {
        can_frame receivedMessage;

        if (xQueueReceive(this->networkToMediatorQueue, &receivedMessage, portMAX_DELAY) == pdTRUE) {
            xQueueSend(this->mediatorToStorageQueue, &receivedMessage, portMAX_DELAY);
        }
    }
}