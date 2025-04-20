#pragma once

#include "Arduino.h"
#include "IPressureSensor.hpp"  // Mocks pressure sensor
#include "IMessageSender.hpp"   

class TirePressureECU{
public:
    TirePressureECU(IPressureSensor&, IMessageSender&);
    void start();
    static void checkPressure(void *param);

private:
    IPressureSensor& pressureSensor;
    IMessageSender& sender;
};
