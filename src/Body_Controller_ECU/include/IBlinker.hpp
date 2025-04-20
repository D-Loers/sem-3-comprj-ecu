#pragma once

class IBlinker{
public:
    virtual ~IBlinker() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};
