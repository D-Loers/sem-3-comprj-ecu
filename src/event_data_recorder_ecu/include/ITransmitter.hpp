#pragma once

#include "mcp2515.h"

class ITransmitter {
public:
    ~ITransmitter() = default;
    virtual bool SendMessage(const can_frame &);
};