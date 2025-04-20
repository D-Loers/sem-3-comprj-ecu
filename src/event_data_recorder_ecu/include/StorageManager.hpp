#pragma once

#include "freertos/FreeRTOS.h"
#include "IStorage.hpp"

class StorageManager {
public:
    StorageManager(IStorage &, QueueHandle_t &);
    ~StorageManager() = default;
    void Run(void);
private:
    IStorage &storage;
    QueueHandle_t &mediatorToStorageQueue;
};