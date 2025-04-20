#pragma once

#include <mcp2515.h>

class IStorage {
public:
    ~IStorage() = default;
    virtual bool Write(can_frame &) = 0;
};