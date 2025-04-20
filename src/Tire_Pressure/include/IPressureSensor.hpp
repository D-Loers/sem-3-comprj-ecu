#pragma once

class IPressureSensor{
public:
    virtual ~IPressureSensor() = default;
    virtual float getPressure(void) = 0;
};