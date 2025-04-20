#pragma once

#include "IPressureSensor.hpp"
#include "Arduino.h"

class PotMeter : public IPressureSensor{
public:
    PotMeter(int pin): pin(pin){pinMode(pin, INPUT);};
    ~PotMeter(){pinMode(pin, OUTPUT);}; // Set back to output for MCU safety

    float getPressure(void) override;
private:
    int pin;
};
