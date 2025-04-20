#pragma once

class IHeadlights{
public:
    virtual ~IHeadlights() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};