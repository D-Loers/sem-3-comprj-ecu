#pragma once

#include "freertos/FreeRTOS.h"
#include "IReceiver.hpp"
#include "IStorage.hpp"

class Mediator {
public:
    Mediator(QueueHandle_t &, QueueHandle_t &);
    ~Mediator() = default;
    void Run(void);
private:
    QueueHandle_t &networkToMediatorQueue;
    QueueHandle_t &mediatorToStorageQueue;
};