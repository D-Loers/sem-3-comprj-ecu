#include "StorageManager.hpp"

#include <Arduino.h>

/* ------ Constructor ------ */

StorageManager::StorageManager(IStorage &storage, QueueHandle_t &mediatorToStorageQueue)
    : storage(storage), mediatorToStorageQueue(mediatorToStorageQueue) {}

/* ------ Public methods ------ */

void StorageManager::Run(void) {
    if (uxQueueMessagesWaiting(this->mediatorToStorageQueue) != 0) {
        can_frame receivedMessage;

        if (xQueueReceive(this->mediatorToStorageQueue, &receivedMessage, portMAX_DELAY) == pdTRUE) {
            this->storage.Write(receivedMessage);
        }
    }
}