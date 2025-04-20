#include <Arduino.h>
#include "CANBus.hpp"
#include "CANBusReceiver.hpp"
#include "BodyControllerECU.hpp"
#include "Blinker.hpp"
#include "Headlights.hpp"

// Pin definitions
#define CAN_CS_PIN 5
#define HEADLIGHTS_PIN 25
#define LEFT_BLINKER_PIN 26
#define RIGHT_BLINKER_PIN 27

// Instantiate components
CANBus canBus(CAN_CS_PIN);
CANBusReceiver canReceiver(canBus);
Headlights headlights(HEADLIGHTS_PIN);
Blinker leftBlinker(LEFT_BLINKER_PIN);
Blinker rightBlinker(RIGHT_BLINKER_PIN);

// Instantiate the ECU
BodyControllerECU ecu(canBus, canReceiver, headlights, leftBlinker, rightBlinker);

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing Body Controller ECU...");

    // Start the ECU
    ecu.start();

    Serial.println("Body Controller ECU initialized.");
}

void loop() {
}
