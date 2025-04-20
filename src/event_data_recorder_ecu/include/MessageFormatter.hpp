#pragma once

#include "mcp2515.h"
#include <string>
#include "MessageInformation.hpp"

class MessageFormatter {
public:
    MessageFormatter() = default;
    ~MessageFormatter() = default;
    std::string GetFormattedMessage(const can_frame &);
private:
    const uint8_t bitmaskSource = 0b111 << 5;
    const uint8_t bitmaskType = 0b11111;
    std::string SetMessageSource(const can_frame &);
    std::string SetMessageType(const can_frame &);
    std::string SetMessageData(const can_frame &);
};