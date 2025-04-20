#pragma once

#include "freertos/FreeRTOS.h"
#include "NetworkManager.hpp"
#include "Mediator.hpp"
#include "StorageManager.hpp"
#include "StorageModule.hpp"
#include "MessageFormatter.hpp"
#include "CANBusTransceiver.hpp"

class EventDataRecorder {
public:
    EventDataRecorder();
    ~EventDataRecorder();
    void Setup();
    
private:
    const int defaultStackSize = 4096;
    const int defaultTaskPriority = 1;
    const int defaultQueueSize = 5;

    CANBusTransceiver receiver;
    MessageFormatter formatter;
    StorageModule storage;

    QueueHandle_t networkToMediatorQueue;
    QueueHandle_t mediatorToStorageQueue;

    TaskHandle_t networkManagerTaskHandle;
    TaskHandle_t mediatorTaskHandle;
    TaskHandle_t storageManagerTaskHandle;

    NetworkManager *networkManager;
    Mediator *mediator;
    StorageManager *storageManager;

    static void NetworkManagerTask(void *param);
    static void MediatorTask(void *param);
    static void StorageManagerTask(void *param);
};