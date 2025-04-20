#pragma once

#include "mcp2515.h"

class IReceiver {
public:
    virtual ~IReceiver() = default;
    virtual bool IsMessageAvailable(void);
    virtual bool GetMessage(can_frame &);
};
