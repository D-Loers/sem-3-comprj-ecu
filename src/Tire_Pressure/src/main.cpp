#include <Arduino.h>
#include "TirePressureECU.hpp"
#include "CANBusSender.hpp"
#include "PotMeter.hpp"

#define CAN_CS_PIN 	5
#define POT_PIN		36

CANBus canBus(CAN_CS_PIN);
CANBusSender canSender(canBus);
PotMeter potMeter(POT_PIN);
TirePressureECU ecu(potMeter, canSender);

void setup(){
	Serial.begin(115200);
	ecu.start();
}

void loop(){
	// Done through RTOS tasks
}