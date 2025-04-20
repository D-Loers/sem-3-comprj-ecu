#include "PotMeter.hpp"

float PotMeter::getPressure(void){
    float pressure;
    int potVal = analogRead(this->pin);
    // Turn pot value into realistisc PSI value
    pressure = 10 + (((float)potVal / (float)4095) * 35);
    Serial.printf("Pressure: %f\n", pressure);
    return pressure;
}