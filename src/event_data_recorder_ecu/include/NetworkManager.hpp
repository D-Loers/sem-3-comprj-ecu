#pragma once

#include <freertos/FreeRTOS.h>
#include "IReceiver.hpp"

class NetworkManager {
public:
    NetworkManager(IReceiver &, QueueHandle_t &);
    ~NetworkManager() = default;
    void Run(void);
private:
    IReceiver &receiver;
    QueueHandle_t &networkToMediatorQueue;
};