#include "CANBusTransceiver.hpp"

/* ------ Constructor ------ */

CANBusTransceiver::CANBusTransceiver() 
    : vspi(VSPI) {
    this->vspi.begin(this->kSCLKPin, this->kMISOPin, this->kMOSIPin, this->kSSPin);
    pinMode(vspi.pinSS(), OUTPUT);
    
    this->CANBus = new MCP2515(this->kSSPin);
    this->CANBus->reset();
    this->CANBus->setBitrate(CAN_500KBPS, MCP_8MHZ);
    this->CANBus->setNormalMode();
}

/* ------ Destructor ------ */

CANBusTransceiver::~CANBusTransceiver() {
    delete this->CANBus;
}

/* ------ Public methods ------ */

bool CANBusTransceiver::SendMessage(const can_frame &message) {
    return this->CANBus->sendMessage(&message) == MCP2515::ERROR_OK;
}

bool CANBusTransceiver::IsMessageAvailable(void) {
    return this->CANBus->checkReceive();
}

bool CANBusTransceiver::GetMessage(can_frame &message) {
    return this->CANBus->readMessage(&message) == MCP2515::ERROR_OK;;
}