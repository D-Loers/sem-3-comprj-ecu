#pragma once

class IMessageSender {
public:
    virtual ~IMessageSender() = default;
    virtual void sendTirePressureUpdate(float) = 0;
    virtual void sendTirePressureWarning() = 0;
};
