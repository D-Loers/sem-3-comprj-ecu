#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include "EventDataRecorder.hpp"

EventDataRecorder *EDR;

void setup() {
    Serial.begin(115200);
    EDR = new EventDataRecorder();
    EDR->Setup();
}

void loop() {
}