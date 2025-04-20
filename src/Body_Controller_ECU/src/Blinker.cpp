#include "Blinker.hpp"

Blinker::Blinker(uint8_t pin)
    : pin(pin), state(false), blinkTaskHandle(nullptr) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

Blinker::~Blinker() {
    if (blinkTaskHandle) {
        vTaskDelete(blinkTaskHandle);
    }
}

void Blinker::turnOn() {
    if (!state) {
        state = true;
        if (!blinkTaskHandle) {
            xTaskCreatePinnedToCore(
                blinkTask,
                "BlinkTask",
                2048,
                this,
                1,
                &blinkTaskHandle,
                0
            );
        }
    }
}

void Blinker::turnOff() {
    if (state) {
        state = false;
        if (blinkTaskHandle) {
            vTaskDelete(blinkTaskHandle);
            blinkTaskHandle = nullptr;
        }
        digitalWrite(pin, LOW); // Ensure the LED is off
    }
}

void Blinker::blinkTask(void* param) {
    Blinker* blinker = static_cast<Blinker*>(param);
    while (blinker->state) {
        digitalWrite(blinker->pin, !digitalRead(blinker->pin)); // Toggle state
        vTaskDelay(pdMS_TO_TICKS(500)); // Blink every 500 ms
    }
    vTaskDelete(nullptr); // Self-delete task
}
