#include "MessageFormatter.hpp"

/* ------ Public methods ------ */

std::string MessageFormatter::GetFormattedMessage(const can_frame &message) {
    return SetMessageSource(message) + "," + SetMessageType(message) + "," + SetMessageData(message);
}

/* ------ Private methods ------ */

std::string MessageFormatter::SetMessageSource(const can_frame &message) {
    uint8_t messageType = (message.can_id & this->bitmaskSource) >> 5;

    switch ((MessageSource)messageType) {
        case MessageSource::EngineController:
            return "Engine controller";

        case MessageSource::BodyController:
            return "Body controller";

        case MessageSource::Infotainment:
            return "Infotainment";

        case MessageSource::TirePressureMonitor:
            return "Tire-pressure monitor";

        case MessageSource::Telematics:
            return "Telematics";
        
        default:
            return "Unkown source";
    }
}

std::string MessageFormatter::SetMessageType(const can_frame &message) {
    uint8_t messageType = message.can_id & this->bitmaskType;

    switch ((MessageTypes)messageType) {
        case MessageTypes::EngineOverheatWarning:
            return "Engine overheat warning";

        case MessageTypes::BrakePressedEvent:
            return "Brake pressed event";

        case MessageTypes::BrakeCommand:
            return "Brake command";

        case MessageTypes::EnginePowerControl:
            return "Engine power control";

        case MessageTypes::HeadlightToggle:
            return "Headlight toggle";

        case MessageTypes::TirePressureWarning:
            return "Tire pressure warning";

        case MessageTypes::TirePressureUpdate:
            return "Tire pressure update";

        case MessageTypes::UserInputForBlinkers:
            return "Blinker input";

        case MessageTypes::GasPedalInput:
            return "Throttle input";

        case MessageTypes::EngineTemperatureUpdate:
            return "Engine temperature update";
        
        default:
            return "Unkown type";
    }
}

std::string MessageFormatter::SetMessageData(const can_frame &message) {
    uint8_t messageType = message.can_id & this->bitmaskType;;

    switch ((MessageTypes)messageType) {
        case MessageTypes::EngineOverheatWarning: {
            bool isEngineOverheating = message.data[0];
            uint16_t engineTemperature = message.data[1] | (message.data[2] << 8);
            return "\"" + std::to_string(isEngineOverheating) + std::to_string(engineTemperature) + "\"";}

        case MessageTypes::BrakePressedEvent: {
            bool isBrakePressed = message.data[0];
            return std::to_string(isBrakePressed);}

        case MessageTypes::BrakeCommand:{
            bool isBrakePressed = message.data[0];
            return std::to_string(isBrakePressed);}

        case MessageTypes::EnginePowerControl: {
            uint8_t throttleApplication = message.data[0];
            return std::to_string(throttleApplication);}

        case MessageTypes::HeadlightToggle: {
            bool isBlinkerOn = message.data[0];
            return std::to_string(isBlinkerOn);}

        case MessageTypes::TirePressureWarning: {
            uint8_t tireID = message.data[0];
            bool isPressureLow = message.data[1];
            return "\"" + std::to_string(tireID) + std::to_string(isPressureLow) + "\"";}

        case MessageTypes::UserInputForBlinkers: {
            std::string blinkerDirection;
            switch (message.data[0]) {
                case 1:
                    blinkerDirection = "Left";
                    break;

                case 2:
                    blinkerDirection = "Right";
                    break;
                
                default:
                    blinkerDirection = "Unkown";
                    break;
            }
            return blinkerDirection;}

        case MessageTypes::GasPedalInput: {
            uint8_t gasPedalInput = message.data[0];
            return std::to_string(gasPedalInput);}

        case MessageTypes::EngineTemperatureUpdate: {
            uint16_t engineTemperature = (uint16_t)message.data[0] | ((uint16_t)message.data[1] << 8);
            return std::to_string(engineTemperature);}
        
        default:
            return "Unkown data";
    }
}